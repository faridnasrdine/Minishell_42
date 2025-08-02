/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:49:01 by houssam           #+#    #+#             */
/*   Updated: 2025/07/30 15:04:04 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_sep(char *path, char *cmd, char c)
{
	char	*s;
	int		i;
	int		len;

	if (!path || !cmd)
		return (NULL);
	len = ft_strlen(path) + ft_strlen(cmd);
	s = malloc(len + 2);
	if (!s)
		return (NULL);
	i = 0;
	while (path[i])
	{
		s[i] = path[i];
		i++;
	}
	s[i++] = c;
	while (*cmd)
	{
		s[i] = *cmd++;
		i++;
	}
	s[i] = '\0';
	return (s);
}

int	exec_run(t_cmd *cmd, t_cmd_exec **env_lst)
{
	if (!ft_strncmp(cmd->path, "pwd", 4))
		return (pwd(env_lst));
	else if (!ft_strncmp(cmd->path, "env", 4))
		return (env(env_lst));
	else if (!ft_strncmp(cmd->path, "unset", 6))
		return (unset(cmd, env_lst));
	else if (!ft_strncmp(cmd->path, "export", 7))
		return (ft_export(cmd, env_lst));
	else if (!ft_strncmp(cmd->path, "echo", 5))
		return (ft_echo(cmd, env_lst));
	else if (!ft_strncmp(cmd->path, "exit", 5))
		return (ft_exit(cmd, env_lst));
	else if (!ft_strncmp(cmd->path, "cd", 3))
		return (ft_cd(cmd, env_lst));
	return (0);
}

static void	close_dups(t_cmd *cmd)
{
	if (cmd->std_in != 0)
	{
		close(0);
		dup2(cmd->std_in_dup1, 0);
		close(cmd->std_in_dup1);
	}
	if (cmd->std_out != 1)
	{
		close(1);
		dup2(cmd->std_out_dup1, 1);
		close(cmd->std_out_dup1);
	}
}

void	exec_run_par(t_cmd *cmd, t_cmd_exec **env_lst)
{
	dups(cmd);
	exec_run(cmd, env_lst);
	close_dups(cmd);
}

void	exec_built(t_cmd *cmd, t_cmd_exec **env_lst, int child_par)
{
	int	exit_code;

	if (!child_par)
		exec_run_par(cmd, env_lst);
	else if (child_par == 1)
	{
		exit_code = exec_run(cmd, env_lst);
		lst_clear(env_lst, free);
		cmd_free(&cmd);
		exit(exit_code);
	}
}
