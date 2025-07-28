/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_child_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:44:03 by houssam           #+#    #+#             */
/*   Updated: 2025/07/28 11:07:43 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_if_dir(t_cmd *exec_cmd, t_cmd_exec **env_lst, char **env)
{
	struct stat	sb;

	if (!ft_strcmp(exec_cmd->args[0], "sudo"))
	{
		ft_putstr_fd("Minishell: : command not found\n", 2);
		lst_clear(env_lst, free);
		arr_free(env);
		cmd_free(&exec_cmd);
		exit(127);
	}
	if (!stat(exec_cmd->path, &sb))
	{
		if (S_ISDIR(sb.st_mode))
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(exec_cmd->path, 2);
			ft_putstr_fd(": is a directory\n", 2);
			lst_clear(env_lst, free);
			arr_free(env);
			cmd_free(&exec_cmd);
			exit(126);
		}
	}
}

t_cmd	*close_pipes(t_cmd **cmd, int id)
{
	t_cmd	*tmp;

	tmp = *cmd;
	while (tmp)
	{
		if (tmp->id != id)
		{
			if (tmp->std_in != 0)
				close(tmp->std_in);
			if (tmp->std_out != 1)
				close(tmp->std_out);
			if (tmp->pipe_out != 0)
				close(tmp->pipe_out);
			if (tmp->pipe_in != 0)
				close(tmp->pipe_in);
		}
		tmp = tmp->next;
	}
	tmp = *cmd;
	while (tmp->id != id)
		tmp = tmp->next;
	dups(tmp);
	return (tmp);
}