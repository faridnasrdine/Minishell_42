/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:19:33 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/02 18:23:45 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_c_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	set_exit_code(130);
	close(0);
}

static int	handle_exit_status(int exit_stat, int *heredoc, t_cmd *cmd)
{
	int	code;

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
	return (-1);
}

static void	set_cmd_stdin(t_cmd *cmd, int fd)
{
	if (cmd->std_in != STDIN_FILENO)
		close(cmd->std_in);
	cmd->std_in = fd;
	ft_signals();
}

int	parent_heredoc(t_cmd *cmd, int *heredoc)
{
	int	exit_stat;
	int	ret;

	signal(SIGINT, SIG_IGN);
	wait(&exit_stat);
	close(heredoc[1]);
	ret = handle_exit_status(exit_stat, heredoc, cmd);
	if (ret != -1)
		return (close(heredoc[0]), ret);
	set_cmd_stdin(cmd, heredoc[0]);
	return (0);
}
