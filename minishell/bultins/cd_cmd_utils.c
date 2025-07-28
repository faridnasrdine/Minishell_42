/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:39:27 by houssam           #+#    #+#             */
/*   Updated: 2025/07/21 22:43:47 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*getold(t_cmd_exec **env_lst)
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

static void	change_env(char *oldpwd, t_cmd_exec *env_lst)
{
	while (env_lst)
	{
		if (!ft_strncmp(env_lst->name, "PWD", 4))
		{
			free(env_lst->value);
			env_lst->value = getcwd(NULL, 0);
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

static int	cd_parent(char *path, t_cmd_exec **env_lst, char *oldpwd)
{
	int	exit_stat;

	wait(&exit_stat);
	if (WIFEXITED(exit_stat))
		exit_stat = WEXITSTATUS(exit_stat);
	if (!exit_stat && !chdir(path))
	{
		change_env(oldpwd, *env_lst);
		free(path);
		change_stat(env_lst, 0);
		return (0);
	}
	if (exit_stat)
		ft_putstr_fd("cd: error retrieving current directory: getcwd: "
			"cannot access parent directories: No such file or "
			"directory\n",
			2);
	else
		perror(path);
	free(path);
	if (oldpwd)
		free(oldpwd);
	change_stat(env_lst, 1);
	return (2);
}

int	change_dir(char *path, t_cmd_exec **env_lst)
{
	char	*old_pwd;
	int		pid;

	old_pwd = getold(env_lst);
	pid = fork();
	if (!pid)
	{
		if (!chdir(path) && getcwd(NULL, 0) == NULL)
			exit(1);
		exit(0);
	}
	else
		return (cd_parent(path, env_lst, old_pwd));
}
