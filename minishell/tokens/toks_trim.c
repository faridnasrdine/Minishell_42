/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toks_trim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:11:35 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/09 21:14:05 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token	*split_into_new_ele(char *str, t_token *tmp)
{
	t_token	*new_elem;

	new_elem = lst_new_ele_tok('o', str);
	new_elem->next = tmp->next;
	return (new_elem);
}

static void	toks_split(t_token **toks)
{
	t_token	*tmp;
	char	**arr;
	int		i;

	tmp = *toks;
	while (tmp)
	{
		if (tmp->type == 'o' && (ft_strchr(tmp->value, ' ') != 0))
		{
			arr = ft_split(tmp->value, ' ');
			tmp->type = 'd';
			i = -1;
			while (arr[++i] != NULL)
			{
				tmp->next = split_into_new_ele(arr[i], tmp);
				tmp = tmp->next;
			}
		}
		tmp = tmp->next;
	}
}

static void	toks_value_trim(t_token *toks)
{
	char	*str;

	while (toks != NULL)
	{
		str = ft_strtrim(toks->value, " ");
		toks->value = str;
		toks = toks->next;
	}
}

void	toks_trim(t_token **toks)
{
	t_token	*tmp1;

	tmp1 = *toks;
	toks_value_trim(*toks);
	toks_split(toks);
	while (tmp1 != NULL)
	{
		if (((ft_strlen(tmp1->value) == 0) || tmp1->type == 'd')
			&& tmp1 == *toks)
		{
			*toks = tmp1->next;
			tmp1 = *toks;
		}
		else if ((tmp1->next) && ((ft_strlen(tmp1->next->value) == 0)
				|| tmp1->next->type == 'd'))
		{
			tmp1->next = tmp1->next->next;
		}
		else if (tmp1)
			tmp1 = tmp1->next;
	}
}
