/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:52:31 by houssam           #+#    #+#             */
/*   Updated: 2025/06/26 21:54:27 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lst_clear(t_cmd_exec **lst, void (*del)(void *))
{
	t_cmd_exec	*tmp;

	if (lst && *lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			lst_del(*lst, del);
			*lst = tmp;
		}
	}
}

void	lst_clear_tok(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;

	if (lst && *lst)
	{
		while (*lst != NULL)
		{
			tmp = (*lst)->next;
			lst_del_tok(*lst, del);
			*lst = tmp;
		}
	}
}
