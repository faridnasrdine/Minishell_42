/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_stat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:12:02 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/07 20:12:04 by nafarid          ###   ########.fr       */
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
	tmp->value = NULL;
	tmp->value = ft_itoa(tmp->status);
}
