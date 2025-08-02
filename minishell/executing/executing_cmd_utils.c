/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_cmd_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:47:17 by houssam           #+#    #+#             */
/*   Updated: 2025/08/01 15:18:43 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**find_and_split(t_cmd_exec *env_lst)
{
	char	**path;

	path = NULL;
	while (env_lst)
	{
		if (!ft_strncmp(env_lst->name, "PATH", 5))
		{
			path = ft_split(env_lst->value, ':');
			break ;
		}
		env_lst = env_lst->next;
	}
	return (path);
}

static char	*find_path(t_cmd_exec *env_lst, char *cmd)
{
	char	**path;
	char	*value;
	int		i;

	i = -1;
	if (!cmd || !cmd[0])
		return NULL;
	path = find_and_split(env_lst);
	while (path && path[++i] != NULL)
	{
		value = ft_strjoin_sep(path[i], cmd, '/');
		if (access(value, X_OK) == 0 || access(value, F_OK) == 0)
		{
			arr_free(path);
			return (value);
		}
		free(value);
	}
	if (path != NULL)
		arr_free(path);
	return (NULL);
}

static int	built(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->args != NULL)
	{
		if (!ft_strncmp(cmd->args[0], "echo", 5))
			i = 1;
		else if (!ft_strncmp(cmd->args[0], "cd", 3))
			i = 1;
		else if (!ft_strncmp(cmd->args[0], "pwd", 4))
			i = 1;
		else if (!ft_strncmp(cmd->args[0], "export", 7))
			i = 1;
		else if (!ft_strncmp(cmd->args[0], "unset", 6))
			i = 1;
		else if (!ft_strncmp(cmd->args[0], "env", 4))
			i = 1;
		else if (!ft_strncmp(cmd->args[0], "exit", 5))
			i = 1;
		cmd->builtin = i;
	}
	return (i);
}

char	*find_cmd(t_cmd *cmd, t_cmd_exec *env_lst)
{
	char	*path;

	path = NULL;
	if (!cmd->args || !cmd->args[0])
	{
		cmd->path_error = 1;
		return (NULL);
	}
	if ((built(cmd) == 1) || (ft_strchr(cmd->args[0], '/') != 0))
		path = cmd->args[0];
	else
	{
		path = find_path(env_lst, cmd->args[0]);
		if (path)
		{
			free(cmd->args[0]);
			cmd->args[0] = path;
		}
	}
	if (!path && cmd->path_error != 4)
		cmd->path_error = 1;
	return (path);
}
