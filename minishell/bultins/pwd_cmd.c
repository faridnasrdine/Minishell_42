/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:50:59 by houssam           #+#    #+#             */
/*   Updated: 2025/07/26 08:27:55 by houssam          ###   ########.fr       */
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

int	pwd(t_cmd_exec **env_lst)
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
