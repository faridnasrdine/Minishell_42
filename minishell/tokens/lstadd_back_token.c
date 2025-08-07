/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_back_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:11:11 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/07 20:11:13 by nafarid          ###   ########.fr       */
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
