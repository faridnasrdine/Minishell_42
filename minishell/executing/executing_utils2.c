/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:00:18 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/05 14:18:01 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	close_open_fd(t_cmd *tmp)
{
	if (tmp->std_in != 0)
	{
		close(tmp->std_in);
		tmp->std_in = 0;
	}
	if (tmp->std_out != 1)
	{
		close(tmp->std_out);
		tmp->std_out = 1;
	}
	if (tmp->pipe_out != 0)
	{
		close(tmp->pipe_out);
		tmp->pipe_out = 0;
	}
	if (tmp->pipe_in != 0)
	{
		close(tmp->pipe_in);
		tmp->pipe_in = 0;
	}
}

void	parent_proc(t_cmd **cmd, t_cmd_exec **env_lst, int idx, int *pids)
{
	t_cmd	*tmp;

	tmp = *cmd;
	while (tmp)
	{
		close_open_fd(tmp);
		tmp = tmp->next;
	}
	waiting(env_lst, cmd, idx, pids);
}

pid_t	*allocate_pid_array(t_cmd *cmd)
{
	pid_t	*pids;

	pids = ft_malloc(sizeof(pid_t) * count_cmds(cmd));
	if (!pids)
		exit(EXIT_FAILURE);
	return (pids);
}
