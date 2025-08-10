/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:07:35 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/10 11:14:40 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_from_envir(t_cmd_exec *env_lst)
{
	while (env_lst)
	{
		if (!ft_strncmp(env_lst->name, "PWD", 4))
		{
			ft_putstr_fd(env_lst->value, 1);
			ft_putchar_fd('\n', 1);
			return (1);
		}
		env_lst = env_lst->next;
	}
	return (0);
}

int	ft_pwd(t_cmd_exec **env_lst)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		if (!get_from_envir(*env_lst))
		{
			errno = 127;
			change_stat(env_lst, 2);
			perror("pwd");
			return (2);
		}
		return (0);
	}
	else
	{
		ft_putstr_fd(path, 1);
		ft_putchar_fd('\n', 1);
		free(path);
		change_stat(env_lst, 0);
		return (0);
	}
}
