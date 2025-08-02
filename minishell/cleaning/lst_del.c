/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:52:18 by houssam           #+#    #+#             */
/*   Updated: 2025/07/28 15:34:26 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lst_del(t_cmd_exec *lst, void (*del)(void *))
{
	if (lst)
	{
		del(lst->name);
		del(lst->value);
		free(lst);
	}
}

void	lst_del_tok(t_token *lst, void (*del)(void *))
{
	if (lst)
	{
		if (lst->value)
			del(lst->value);
		del(lst->quote);
		free(lst);
	}
	lst =NULL;
}
