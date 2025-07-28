/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:50:35 by houssam           #+#    #+#             */
/*   Updated: 2025/07/23 11:54:06 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_error(char *str)
{
	char	*tmp;
	char	*err;

	tmp = ft_strjoin(str, "': not a valid identifier\n");
	err = ft_strjoin("Minishell: '", tmp);
	free(tmp);
	ft_putstr_fd(err, 2);
	free(err);
}

int	check_var_name(char *str, int *res, t_cmd_exec **env_lst)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!i && ((str[0] == '_') || (str[0] >= 'a' && str[0] <= 'z')
				|| (str[0] >= 'A' && str[0] <= 'Z')))
			continue ;
		else if (i && ((str[i] >= 48 && str[i] <= 57) || (str[i] >= 'a'
					&& str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] == '_')))
			continue ;
		else
		{
			print_error(str);
			change_stat(env_lst, 1);
			*res = 1;
			return (1);
		}
	}
	return (0);
}
