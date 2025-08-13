/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:14:17 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/13 11:10:46 by nafarid          ###   ########.fr       */
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
	int		pid;
	int		fd[2];
	char	*herdoc_file;

	herdoc_file = file_random();
	fd[1] = open(herdoc_file, O_CREAT | O_WRONLY, 0664);
	if (fd[1] == -1)
		return (1);
	fd[0] = open(herdoc_file, O_CREAT | O_RDONLY, 0664);
	if (fd[0] == -1)
	{
		close(fd[1]);
		return (1);
	}
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (!pid)
		child_heredoc(cmd, env_lst, fd);
	else
		return (parent_heredoc(pid, cmd, fd));
	return (0);
}
