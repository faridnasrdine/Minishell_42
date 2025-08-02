/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:21:01 by houssam           #+#    #+#             */
/*   Updated: 2025/08/02 17:22:23 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*line_expansion(char *line, t_cmd_exec *env_lst)
{
	t_token	*tmp;
	char	*str;

	tmp = malloc(sizeof(t_token));
	if (!tmp)
		return (NULL);
	tmp->value = line;
	tmp->type = 'w';
	tmp->quote = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!tmp->quote)
		return (NULL);
	tmp->quote[ft_strlen(line)] = '\0';
	tmp->quote = ft_memset(tmp->quote, '0', ft_strlen(line));
	tmp->next = NULL;
	p_expansion(tmp, env_lst);
	free(tmp->quote);
	str = tmp->value;
	free(tmp);
	return (str);
}

static void    go_heredoc(t_cmd *cmd, t_cmd_exec *env_lst, int fd_doc)
{
    char    *line;
    char    *processed_line;

    while (1)
    {
        line = readline("heredoc> ");
        if (get_exit_code() == 130)
        {
            if (line)
                free(line);
            lst_clear(&env_lst, &free);
            cmd_free(&cmd);
			exit(130);
        }
        if (!line)
        {
            lst_clear(&env_lst, &free);
            cmd_free(&cmd);
            ft_putstr_fd("Minishell: warning: here-document at line 1 delimited by end-of-file (wanted `\n", 2);
			ft_putstr_fd(processed_line, 2);
			break ;
        }        
        if (!ft_strncmp(line, cmd->op_value, ft_strlen(cmd->op_value)) && 
            ft_strlen(line) == ft_strlen(cmd->op_value))
        {
            free(line);
            break ;
        }        
        if (cmd->delimiter == 'h')
        {
            processed_line = line_expansion(line, env_lst);
            if (!processed_line)
            {
                lst_clear(&env_lst, &free);
                cmd_free(&cmd);
                exit(1);
            }
        }
        else
            processed_line = line;      
		ft_putstr_fd(processed_line, fd_doc);
		ft_putstr_fd("\n", fd_doc);
        free(processed_line);
    }
}

static void	child_heredoc(t_cmd *cmd, t_cmd_exec **env_lst, int *heredoc)
{
	signal(SIGINT, handle_ctrl_c_heredoc);
	close(heredoc[0]);
	go_heredoc(cmd, *env_lst, heredoc[1]);
	close(heredoc[1]);
	exit(0);
}

static int	parent_heredoc(t_cmd *cmd, int *heredoc)
{
	int	exit_stat;
	int	code;
	
	signal(SIGINT, SIG_IGN);
	wait(&exit_stat);
	close(heredoc[1]);
	if (WIFEXITED(exit_stat))
	{
		code = WEXITSTATUS(exit_stat);
		if (code == 1)
		{
			close(heredoc[0]);
			return (-3);
		}
		else if (code == 0)
		{
			if (cmd->std_in != STDIN_FILENO)
			close(cmd->std_in);
			cmd->std_in = heredoc[0];
			ft_signals();
			return (0); 
		}
	}
	if (cmd->std_in != STDIN_FILENO)
		close(cmd->std_in);
	cmd->std_in = heredoc[0];
	ft_signals();
	return (0);
}

int	heredoc(t_cmd *cmd, t_cmd_exec **env_lst)
{
	int	pid;
	int	heredoc[2];
	int	i;

	i = pipe(heredoc);
	if (i == -1)
		exit(1);
	pid = fork();
	if (!pid)
		child_heredoc(cmd, env_lst, heredoc);
	else
		return (parent_heredoc(cmd, heredoc));
	return (0);
}
