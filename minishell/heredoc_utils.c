/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:19:33 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/10 13:46:49 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_exit_status(int exit_stat, int *heredoc, t_cmd *cmd)
{
	int	code;
	int	sig;

	if (WIFEXITED(exit_stat))
	{
		code = WEXITSTATUS(exit_stat);
		sig = WIFSIGNALED(exit_stat);
		if (sig == SIGINT)
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
	return (-1);
}

static void	set_cmd_stdin(t_cmd *cmd, int fd)
{
	if (cmd->std_in != STDIN_FILENO)
		close(cmd->std_in);
	cmd->std_in = fd;
	ft_signals();
}

int	parent_heredoc(pid_t pid, t_cmd *cmd, int *heredoc)
{
	int	exit_stat;
	int	ret;

	waitpid(pid, &exit_stat, 0);
	if (WIFEXITED(exit_stat))
	{
		set_exit_code(WEXITSTATUS(exit_stat));
	}
	close(heredoc[1]);
	ret = handle_exit_status(exit_stat, heredoc, cmd);
	if (ret != -1)
		return (ret);
	set_cmd_stdin(cmd, heredoc[0]);
	return (0);
}

char	*file_random(void)
{
	char	buffer[10];
	char	c;
	int		i;
	int		fd;

	i = 0;
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (NULL);
	while (i < 10)
	{
		if (read(fd, &c, 1) <= 0)
			return (close(fd), NULL);
		if (ft_isalnum(c))
			buffer[i++] = c;
	}
	buffer[i] = '\0';
	close(fd);
	return (ft_strjoin("/tmp/", buffer));
}

void	handle_ctrl_c_heredoc(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	restore_std_fds();
	free_grabage();
	exit(130);
}
