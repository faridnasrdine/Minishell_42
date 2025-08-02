/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 00:32:42 by hounejja          #+#    #+#             */
/*   Updated: 2025/08/01 19:25:58 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_replace(t_token *toks, int i, int j, t_cmd_exec *env_lst)
{
	char	*value;
	int		k;

	k = 0;
	toks->strip = 0;
	while (toks->value[k])
	{
		if ((!toks->value[k + 1] && toks->value[k] == '$') || 
			(toks->value[k] == '$' && toks->value[k + 1] == '.'))
			toks->strip = 0;
		k++;
	}
	if (toks->strip && toks->value[i - 1] != '=')
		value = erase_spaces(env_lst->value);
	else
		value = ft_strdup(env_lst->value);
	if (!value)
		return (-1);
	build_new_tok_val(toks, value, i, j);
	if (toks->strip != 2)
	{
		if (split_token_into_nodes(toks) == -1)
			return (-1);
	}
	if (copy_quotes(toks, env_lst, i, j) == -1)
		return (-1);
	return (0);
}

static int	ft_is_found2(t_token *toks, int *i, int j, t_cmd_exec *tmp)
{
	if ((j - *i) == 1 && (tmp->name[0] == '1' || (toks->value[j] != '\"'
				&& toks->value[j] != '\'')))
		tmp->value = malloc(sizeof(char) * 2);
	else
		tmp->value = malloc(sizeof(char) * 1);
	if (!tmp->value)
		return (-1);
	if ((j - *i) == 1 && (tmp->name[0] == 1 || (toks->value[j] != '\"'
				&& toks->value[j] != '\'')))
	{
		tmp->value[0] = '$';
		tmp->value[1] = '\0';
	}
	else
		tmp->value[0] = '\0';
	tmp->next = NULL;
	return (1);
}

static int	ft_is_found(t_token *toks, int *i, int j, int quote)
{
	t_cmd_exec	*tmp;
	int			res;

	toks->strip = (quote == 0);	
	tmp = malloc(sizeof(t_cmd_exec) * 1);
	if (!tmp)
		return (-1);
	tmp->name = malloc(sizeof(char) * 2);
	if (!tmp->name)
		return (free(tmp), -1);
	if (quote == 1)
		tmp->name[0] = '1';
	else
		tmp->name[0] = '0';
	tmp->name[1] = '\0';
	ft_is_found2(toks, i, j, tmp);
	res = ft_replace(toks, *i, j, tmp);
	if (!((j - *i) == 1 && (tmp->name[0] == '1' || (toks->value[j] == '\"'
					|| toks->value[j] == '\''))))
		*i = *i - 1;
	lst_del(tmp, free);
	return (res);
}

static int	search_and_replace(t_token *t, int *i, t_cmd_exec *env_lst, int w)
{
	char	*new_str;
	int		j;
	int		inside_word;
	int		start_pos;
	
	start_pos = *i;
	j = *i + 1;
	func(t, &j);
	new_str = ft_substr(t->value, *i + 1, j - *i - 1);
	if (!new_str)
		return (-1);
	if (!new_str[0])
		return (free(new_str),(*i)++,  0);
	while (env_lst && ft_strncmp(env_lst->name, new_str, ft_strlen(new_str)
		+ 1))
		env_lst = env_lst->next;
	free(new_str);
	inside_word = (*i > 0 && !ft_strchr(" \t/$.<>|", t->value[*i - 1]));
	if (env_lst)
	{
		if (inside_word)
			t->strip = (w == 0);
		else
			t->strip = 1;
		if (ft_replace(t, *i, j, env_lst) == -1)
			return (-1);
		*i = start_pos + ft_strlen(env_lst->value) - 1;
		return (0);
	}
	return (t->strip = !(inside_word), ft_is_found(t, i, j, w));
}

void	p_expansion(t_token *toks, t_cmd_exec *env_lst)
{
	int	i;

	i = 0;
	toks->expanded = 0;
	while (toks->value && toks->value[i])
	{
		if (toks->value[i] == '\'')
		{
			i++;
			while (toks->value[i] != '\'' && toks->value[i])
				i++;
			if (toks->value[i] == '\'')
				i++;
		}
		else if (toks->value[i] == '\"')
		{
			i++;
			while (toks->value[i] && toks->value[i] != '\"')
			{
				if (toks->value[i] == '$')
				{
					if (search_and_replace(toks, &i, env_lst, 1) == -1)
					{
						toks->expanded = 1;
						return ;
					}
					toks->expanded = 1;
				}
				i++;
			}
			if (toks->value[i] == '\"')
				i++;
		}
		else if (toks->value[i] == '$')
		{
			if (search_and_replace(toks, &i, env_lst, 0) == -1)
			{
				toks->expanded = 1;
				return ;
			}
			toks->expanded = 1;
			i++;
		}
		else
			i++;
	}
}
