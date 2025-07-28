/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:51:15 by houssam           #+#    #+#             */
/*   Updated: 2025/06/26 21:51:17 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env(t_cmd_exec **env_lst)
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
		arr_free(env);
		change_stat(env_lst, 0);
		return (0);
	}
	else
	{
		arr_free(env);
		change_stat(env_lst, 127);
		return (2);
	}
}
