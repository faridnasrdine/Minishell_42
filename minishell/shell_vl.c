/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_vl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:15:49 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/07 20:15:54 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_single_quotes(t_token *toks, int i)
{
	i++;
	while (toks->value[i] != '\'' && toks->value[i])
		i++;
	if (toks->value[i] == '\'')
		i++;
	return (i);
}

int	handle_dollar_sign(t_token *toks, int i, t_cmd_exec *env_lst)
{
	if (toks->value[i + 1] == '?')
	{
		search_and_replace(toks, &i, env_lst, 0);
		return (-1);
	}
	else if (search_and_replace(toks, &i, env_lst, 0) == -1)
	{
		toks->expanded = 1;
		return (-1);
	}
	toks->expanded = 1;
	return (i + 1);
}

int	len_till_expansion(char *s, int start_pos)
{
	int	i;
	int	in_quotes;
	int	len;

	if (!s || start_pos < 0)
		return (0);
	len = ft_strlen(s);
	if (start_pos >= len)
		return (0);
	i = start_pos;
	in_quotes = 0;
	while (s[i])
	{
		if (s[i] == '\"' && !in_quotes)
			in_quotes = 1;
		else if (s[i] == '\"' && in_quotes)
			in_quotes = 0;
		else if (!in_quotes && (s[i] == ' ' || s[i] == '\t'))
			break ;
		i++;
	}
	return (i - start_pos);
}

void	build_new_tok_val(t_token *toks, char *value, int i, int j)
{
	char	*prefix;
	char	*suffix;
	char	*new_val;

	prefix = ft_substr(toks->value, 0, i);
	suffix = ft_strdup(toks->value + j);
	new_val = ft_strjoin(prefix, value);
	value = ft_strjoin(new_val, suffix);
	toks->value = value;
	check_if_should_split(toks);
}

char	*erase_spaces(char *str)
{
	int		i;
	int		j;
	int		space;
	char	*res;

	res = ft_malloc(ft_strlen(str) + 1);
	i = -1;
	j = 0;
	if (!res)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == 32 || str[i] == '\t')
		{
			if (!space)
				res[j++] = ' ';
			space = 1;
		}
		else
		{
			res[j++] = str[i];
			space = 0;
		}
	}
	return (res[j] = '\0', res);
}
