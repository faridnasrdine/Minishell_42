/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:39:27 by houssam           #+#    #+#             */
/*   Updated: 2025/07/30 11:47:33 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*getold(t_cmd_exec **env_lst)
{
	t_cmd_exec	*tmp;

	tmp = *env_lst;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "PWD", 4) && tmp->meaning != 'p')
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

void	change_env(char *oldpwd, char *newpwd, t_cmd_exec *env_lst)
{
	while (env_lst)
	{
		if (!ft_strncmp(env_lst->name, "PWD", 4))
		{
			free(env_lst->value);
			env_lst->value = ft_strdup(newpwd);
		}
		else if (!ft_strncmp(env_lst->name, "OLDPWD", 7))
		{
			if (env_lst->value)
				free(env_lst->value);
			if (!oldpwd)
			{
				env_lst->value = ft_strdup("");
				env_lst->meaning = 'q';
			}
			else
				env_lst->value = ft_strdup(oldpwd);
		}
		env_lst = env_lst->next;
	}
}

static char	*get_env_pwd(t_cmd_exec *env_lst)
{
	while (env_lst)
	{
		if (!ft_strncmp(env_lst->name, "PWD", 4))
			return (env_lst->value);
		env_lst = env_lst->next;
	}
	return (NULL);
}

static char	*construct_path(char *env_pwd, char *path)
{
	char	*new_pwd;
	int		len;

	len = ft_strlen(env_pwd) + ft_strlen(path) + 2;
	new_pwd = malloc(sizeof(char) * len);
	if (!new_pwd)
		return (NULL);
	ft_strlcpy(new_pwd, env_pwd, ft_strlen(env_pwd) + 1);
	if (env_pwd[ft_strlen(env_pwd) - 1] != '/')
		ft_strlcat(new_pwd, "/", len);
	ft_strlcat(new_pwd, path, len);
	return (new_pwd);
}

char	*check_dir(t_cmd_exec **env_lst, char *path)
{
	char	*new_pwd;
	char	*env_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		env_pwd = get_env_pwd(*env_lst);
		if (env_pwd && path[0] != '/')
			new_pwd = construct_path(env_pwd, path);
		else
			new_pwd = ft_strdup(path);
		ft_putstr_fd("cd: error retrieving current directory: getcwd: "
			"cannot access parent directories: No such file or "
			"directory\n", 2);
	}
	return (new_pwd);
}
