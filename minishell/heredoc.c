/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hounejja <hounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:21:01 by houssam           #+#    #+#             */
/*   Updated: 2025/08/05 04:25:44 by hounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*line_expansion(char *line, t_cmd_exec *env_lst)
{
	t_token	*tmp;
	char	*str;

	tmp = ft_malloc(sizeof(t_token));
	if (!tmp)
		return (NULL);
	tmp->value = line;
	tmp->type = 'w';
	tmp->quote = ft_malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!tmp->quote)
		return (NULL);
	tmp->quote[ft_strlen(line)] = '\0';
	tmp->quote = ft_memset(tmp->quote, '0', ft_strlen(line));
	tmp->next = NULL;
	p_expansion(tmp, env_lst);
	str = tmp->value;
	return (str);
}

static void	handle_ctrl_d_heredoc(char *line, t_cmd *cmd)
{
	if (get_exit_code() == 130)
	{
		restore_std_fds();
		free_grabage();
		exit(0);
	}
	if (!line)
	{
		ft_putstr_fd("\nMinishell: warning: here-document at ", 2);
		ft_putstr_fd("line 1 delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(cmd->op_value, 2);
		ft_putstr_fd("')\n", 2);
		restore_std_fds();
		free_grabage();
		exit(0);
	}
}

static void	go_heredoc(t_cmd *cmd, t_cmd_exec *env_lst, int fd_doc)
{
	char	*line;
	char	*processed_line;

	while (1)
	{
		line = readline("heredoc> ");
		handle_ctrl_d_heredoc(line, cmd);
		if (!ft_strncmp(line, cmd->op_value, ft_strlen(cmd->op_value))
			&& ft_strlen(line) == ft_strlen(cmd->op_value))
			break ;
		if (cmd->delimiter == 'h')
		{
			processed_line = line_expansion(line, env_lst);
			if (!processed_line)
			{
				free_grabage();
				exit(1);
			}
		}
		else
			processed_line = line;
		ft_putstr_fd(processed_line, fd_doc);
		ft_putstr_fd("\n", fd_doc);
	}
}

static void	child_heredoc(t_cmd *cmd, t_cmd_exec **env_lst, int *heredoc)
{
	signal(SIGINT, handle_ctrl_c_heredoc);
	close(heredoc[0]);
	go_heredoc(cmd, *env_lst, heredoc[1]);
	close(heredoc[1]);
	restore_std_fds();
	free_grabage();
	exit(0);
}

int	heredoc(t_cmd *cmd, t_cmd_exec **env_lst)
{
	int	pid;
	int	heredoc[2];
	int	i;

	i = pipe(heredoc);
	if (i == -1)
		exit((perror("Minishell: "), 1));
	pid = fork();
	if (!pid)
		child_heredoc(cmd, env_lst, heredoc);
	else
		return (parent_heredoc(cmd, heredoc));
	return (0);
}
