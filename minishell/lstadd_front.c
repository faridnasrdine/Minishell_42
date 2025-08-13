/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_front.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:14:46 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/13 11:14:05 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_if_should_split(t_token *toks)
{
	int	k;
	int	in_quotes;

	k = -1;
	in_quotes = 0;
	while (toks->value[++k])
	{
		if (toks->value[k] == '"' && !in_quotes)
			in_quotes = 1;
		else if (toks->value[k] == '"' && in_quotes)
			in_quotes = 0;
		else if ((toks->value[k] == '$' && !toks->value[k + 1])
			|| ft_strchr("=.\'", toks->value[k]) || in_quotes)
		{
			toks->strip = 2;
			return ;
		}
	}
}

void	ft_lstadd_front(t_cmd_exec **lst, t_cmd_exec *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

void	ft_exitt(int *status)
{
	if (get_exit_code() == 130)
		exit((ft_putstr_fd("\nexit\n", 2), free_grabage(), get_exit_code()));
	else
		exit((ft_putstr_fd("\nexit\n", 2), free_grabage(), *status));
}
