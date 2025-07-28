/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:21:45 by houssam           #+#    #+#             */
/*   Updated: 2025/07/25 15:46:04 by houssam          ###   ########.fr       */
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

t_cmd_exec	*search_and_replace_helper(t_cmd_exec *env_lst, int *i, int j,
		t_token *t)
{
	char		*new_str;
	t_cmd_exec	*tmp;

	new_str = ft_substr(t->value, *i + 1, j - *i - 1);
	if (!new_str || !new_str[0])
		return (NULL);
	tmp = env_lst;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, new_str, ft_strlen(new_str) + 1))
			break ;
		tmp = tmp->next;
	}
	if (!new_str[0])
		return (free(new_str), NULL);
	free(new_str);
	return (tmp);
}

void	remove_empty_tokens(t_token **toks)
{
	t_token	*curr;
	t_token	*to_delete;
	t_token	*prev;

	curr = *toks;
	prev = NULL;
	while (curr && curr->type != 'r')
	{
		if (curr->value && (!curr->value[0] || curr->value[0] == 32))
		{
			to_delete = curr;
			if (prev)
				prev->next = curr->next;
			else
				*toks = curr->next;
			curr = curr->next;
			lst_clear_tok(&to_delete, &free);
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

char	*ft_strdup_repeat(char c, size_t len)
{
	size_t	i;
	char	*res;

	i = 0;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	while (i < len)
		res[i++] = c;
	res[len] = '\0';
	return (res);
}

int	copy_quotes(t_token *t, t_cmd_exec *env_lst, int i, int j)
{
	char	*new_quote;
	char	*new_str;
	char	*final;
	int		env_len;

	env_len = ft_strlen(env_lst->value);
	if (i > (int)ft_strlen(t->quote) || j > (int)ft_strlen(t->quote))
		return (-1);
	new_quote = malloc(env_len + 1);
	if (!new_quote)
		return (-1);
	ft_memset(new_quote, '2', env_len);
	new_quote[env_len] = '\0';
	t->quote[i] = '\0';
	new_str = ft_strjoin(t->quote, new_quote);
	free(new_quote);
	if (!new_str)
		return (-1);
	final = ft_strjoin(new_str, t->quote + j);
	free(new_str);
	if (!final)
		return (-1);
	free(t->quote);
	t->quote = final;
	return (0);
}
