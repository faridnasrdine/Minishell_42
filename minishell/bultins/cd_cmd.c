/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:45:37 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/02 11:35:47 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	find_home(t_cmd_exec **env_lst, char **path)
{
	t_cmd_exec	*tmp;

	tmp = *env_lst;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "HOME", 5))
		{
			*path = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
	{
		ft_putstr_fd("Minishell: cd: HOME not set", 2);
		change_stat(env_lst, 1);
		return (-1);
	}
	return (0);
}

static int	change_dir(char *path, t_cmd_exec **env_lst)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = getold(env_lst);
	if (chdir(path) != 0)
	{
		perror(path);
		change_stat(env_lst, 1);
		return (1);
	}
	new_pwd = check_dir(env_lst, path);
	change_env(old_pwd, new_pwd, *env_lst);
	change_stat(env_lst, 0);
	return (0);
}

int	ft_cd(t_cmd *cmd, t_cmd_exec **env_lst)
{
	char	*path;
	int		res;

	res = 0;
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
		change_stat(env_lst, 1);
		return (1);
	}
	if (!cmd->args[1])
		res = find_home(env_lst, &path);
	else
		path = ft_strdup(cmd->args[1]);
	if (!res)
		res = change_dir(path, env_lst);
	return (res);
}
