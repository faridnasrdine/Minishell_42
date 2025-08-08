/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:07:04 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/08 14:06:37 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_cmd_exec **env_lst)
{
	int		i;
	char	**env;

	i = -1;
	env = env_lst_to_arr(*env_lst, 'e', 0);
	while (env[++i])
	{
		ft_putstr_fd(env[i], 1);
		ft_putchar_fd('\n', 1);
	}
	if (!env[i])
	{
		change_stat(env_lst, 0);
		return (0);
	}
	else
	{
		change_stat(env_lst, 127);
		return (2);
	}
}
