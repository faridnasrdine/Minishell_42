/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:16:12 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/09 12:09:25 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_quote_removal(t_token **toks)
{
	t_token	*tmp;

	tmp = *toks;
	if (!tmp || !tmp->value || !tmp->quote)
		return ;
	while (tmp && tmp->type != 'c')
	{
		if (tmp->type != 'r')
			quote_del(tmp);
		tmp = tmp->next;
	}
}

t_token	*new_ele_tok_node(char **words, int i)
{
	t_token	*curr;

	curr = ft_malloc(sizeof(t_token));
	if (!curr)
		return (NULL);
	curr->type = 'w';
	curr->value = ft_strdup(words[i]);
	curr->quote = ft_strdup("0");
	curr->next = NULL;
	if (!curr->value || !curr->quote)
		return (NULL);
	return (curr);
}

static int	ft_split_token_into_nodes_2(t_token *curr, char **words,
		t_token *next)
{
	int		i;
	t_token	*new;

	i = 0;
	while (words[++i])
	{
		new = new_ele_tok_node(words, i);
		if (!new)
			return (-1);
		curr->next = new;
		curr = new;
	}
	curr->next = next;
	return (0);
}

int	split_token_into_nodes(t_token *tok)
{
	char	**words;
	t_token	*curr;
	t_token	*next;

	if (!tok || !tok->value || !tok->value[0])
		return (-1);
	curr = tok;
	next = tok->next;
	words = ft_split(tok->value, ' ');
	if (!words || !words[0])
		return (-1);
	curr->value = ft_strdup(words[0]);
	curr->quote = ft_strdup("0");
	if (!curr->value || !curr->quote)
		return (-1);
	if (ft_split_token_into_nodes_2(curr, words, next) == -1)
		return (-1);
	return (0);
}
