/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_stat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:18:40 by houssam           #+#    #+#             */
/*   Updated: 2025/06/26 22:18:42 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_stat(t_cmd_exec **env_lst, int stat)
{
	t_cmd_exec	*tmp;

	tmp = *env_lst;
	while (tmp->meaning != '?')
		tmp = tmp->next;
	tmp->status = stat;
	if (tmp->value)
		free(tmp->value);
	tmp->value = ft_itoa(tmp->status);
}
