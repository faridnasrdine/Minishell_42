/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_child_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:08:43 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/12 18:29:40 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_cmds(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

void	check_if_dir(t_cmd *exec_cmd)
{
	struct stat	sb;

	if (!stat(exec_cmd->path, &sb))
	{
		if (S_ISDIR(sb.st_mode))
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(exec_cmd->path, 2);
			ft_putstr_fd(": is a directory\n", 2);
			free_grabage();
			exit(126);
		}
		else if (S_ISREG(sb.st_mode) && access(exec_cmd->path, X_OK))
		{
			perror("Minishell: ");
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

char	*check_is_path_fail(t_cmd *cmd)
{
	char	*path;

	path = ft_strjoin("./", cmd->args[0]);
	if (access(path, X_OK) == 0)
		return (path);
	if (access(path, F_OK) == 0)
		return (NULL);
	check_if_dir(cmd);
	return (NULL);
}
