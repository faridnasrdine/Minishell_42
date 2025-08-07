/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:08:57 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/07 20:08:59 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	helper(t_token *toks, int *i, char c)
{
	toks->quote[*i] = '1';
	while (toks->value[++(*i)] != c)
		toks->quote[*i] = '0';
	toks->quote[*i] = '1';
}

static void	ensure_quote_allocated(t_token *t)
{
	if (!t->quote || ft_strlen(t->quote) < ft_strlen(t->value))
	{
		t->quote = ft_calloc(ft_strlen(t->value) + 1, sizeof(char));
	}
}

void	quote_count(t_token *toks)
{
	int	i;

	i = -1;
	if (toks != NULL)
	{
		ensure_quote_allocated(toks);
		while (toks->value[++i])
		{
			if (toks->value[i] == '\'')
				helper(toks, &i, '\'');
			else if (toks->value[i] == '\"')
				helper(toks, &i, '\"');
			else
				toks->quote[i] = '0';
		}
	}
}
