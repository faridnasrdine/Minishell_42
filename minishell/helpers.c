/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:21:45 by houssam           #+#    #+#             */
/*   Updated: 2025/08/03 18:26:04 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	func(t_token *t, int *j)
{
	if (t->value[*j] == '?')
	{
		(*j)++;
		return ;
	}
	else
	{
		while (t->value[*j] && !ft_strchr(" \t\"\'/?$=[]:.<>|", t->value[*j])
				&& ft_isalpha(t->value[*j]))
			(*j)++;
		while (t->value[*j] == '_' || ft_isalpha(t->value[*j]))
			(*j)++;
	}
}

static int	should_remove_token(t_token *tok)
{
	int	i;

	i = 0;
	if (!tok || tok->type == 'r' || tok->type == 'c')
		return (0);
	if (!tok->value)
		return (1);
	if (!tok->value[0])
		return (1);
	while (tok->value[i])
	{
		if (tok->value[i] != ' ' && tok->value[i] != '\t'
			&& tok->value[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

void	remove_empty_tokens(t_token **toks)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*next;

	if (!toks || !*toks)
		return ;
	curr = *toks;
	prev = NULL;
	while (curr && curr->type != 'c')
	{
		next = curr->next;
		if (curr->type == 'r')
		{
			prev = curr;
			curr = next;
			continue ;
		}
		if (should_remove_token(curr))
		{
			if (prev)
				prev->next = next;
			else
				*toks = next;
			curr = next;
		}
		else
		{
			prev = curr;
			curr = next;
		}
	}
}

int	copy_quotes(t_token *t, t_cmd_exec *env_lst, int i, int j)
{
	char	*new_quote;
	char	*new_str;
	char	*final;
	int		env_len;

	env_len = ft_strlen(env_lst->value);
	// if (i > (int)ft_strlen(t->quote) || j > (int)ft_strlen(t->quote))
	// 	return (-1);
	new_quote = ft_malloc(env_len + 1);
	if (!new_quote)
		return (-1);
	ft_memset(new_quote, '2', env_len);
	new_quote[env_len] = '\0';
	t->quote[i] = '\0';
	new_str = ft_strjoin(t->quote, new_quote);
	if (!new_str)
		return (-1);
	final = ft_strjoin(new_str, t->quote + j);
	if (!final)
		return (-1);
	t->quote = final;
	return (0);
}
