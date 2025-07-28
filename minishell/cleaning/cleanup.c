/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:00:16 by nafarid           #+#    #+#             */
/*   Updated: 2025/07/28 14:49:36 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup(t_cmd_exec **env_lst, t_cmd **cmd,
	t_cmd *exec_cmd, char **env)
{
	if (env)
		arr_free(env);
	if (env_lst)
		lst_clear(env_lst, free);
	if (exec_cmd && exec_cmd != *cmd)
		cmd_free(&exec_cmd);
	if (cmd)
		cmd_free(cmd);
}
