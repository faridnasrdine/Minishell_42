/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_cmd_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:08:10 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/12 18:31:33 by nafarid          ###   ########.fr       */
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
	char		**path;
	char		*value;
	char		*tmp;
	struct stat	check;
	int			i;

	i = -1;
	if (!cmd || !cmd[0])
		return (NULL);
	path = find_and_split(env_lst);
	tmp = NULL;
	while (path && path[++i] != NULL)
	{
		value = ft_strjoin_sep(path[i], cmd, '/');
		if (access(value, F_OK) == 0 && !stat(value, &check)
			&& !S_ISDIR(check.st_mode))
		{
			if (access(value, X_OK) == 0)
				return (value);
			tmp = value;
		}
	}
	return (tmp);
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

static void	handle_path_error(t_cmd *cmd, t_cmd_exec *env_lst)
{
	t_cmd_exec	*env_tmp;
	int			path_exists;

	env_tmp = env_lst;
	path_exists = 0;
	while (env_tmp)
	{
		if (!ft_strncmp(env_tmp->name, "PATH", 4))
		{
			path_exists = 1;
			break ;
		}
		env_tmp = env_tmp->next;
	}
	if (!path_exists)
		cmd->path_error = 2;
	else
	{
		if (!env_tmp->value || !env_tmp->value[0])
			cmd->path_error = 2;
		else
			cmd->path_error = 1;
	}
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
	if ((built(cmd) == 1) || ft_strchr(cmd->args[0], '/'))
		path = cmd->args[0];
	else
	{
		path = find_path(env_lst, cmd->args[0]);
		if (!path)
			handle_path_error(cmd, env_lst);
		else
			cmd->args[0] = path;
	}
	return (path);
}
