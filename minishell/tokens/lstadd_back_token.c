/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_back_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:55:13 by houssam           #+#    #+#             */
/*   Updated: 2025/06/26 21:55:15 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lstadd_back_tok(t_token **lst, t_token *node)
{
	t_token	*tmp;

	if (lst)
	{
		if (*lst == NULL)
			*lst = node;
		else
		{
			tmp = lst_last_tok(*lst);
			tmp->next = node;
		}
	}
}
