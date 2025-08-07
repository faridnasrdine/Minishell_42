/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:12:54 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/07 20:12:56 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*new_ele(char **parts, t_token *last, int i)
{
	t_token	*curr;

	curr = ft_malloc(sizeof(t_token));
	if (!curr)
		return (NULL);
	curr->value = ft_strdup(parts[i]);
	curr->quote = ft_strdup(parts[i]);
	curr->next = last->next;
	return (curr);
}

int	handle_split(t_token *toks, char *value)
{
	char	**parts;
	t_token	*new;
	t_token	*last;
	int		i;

	parts = ft_split(value, ' ');
	if (!parts)
		return (-1);
	toks->value = NULL;
	toks->quote = NULL;
	toks->value = ft_strdup(parts[0]);
	toks->quote = ft_strdup(parts[0]);
	if (!toks->value || !toks->quote)
		return (-1);
	last = toks;
	i = 0;
	while (parts[++i])
	{
		new = new_ele(parts, last, i);
		if (!new)
			return (-1);
		last->next = new;
		last = new;
	}
	return (0);
}
