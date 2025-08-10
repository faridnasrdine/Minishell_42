/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:00:18 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/10 10:05:33 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parent_proc(t_cmd_exec **env_lst, int idx, int *pids)
{
	restore_std_fds();
	waiting(env_lst, idx, pids);
}

pid_t	*allocate_pid_array(t_cmd *cmd)
{
	pid_t	*pids;

	pids = ft_malloc(sizeof(pid_t) * count_cmds(cmd));
	if (!pids)
		exit(EXIT_FAILURE);
	return (pids);
}
