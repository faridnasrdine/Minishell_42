/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_front.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:20:22 by houssam           #+#    #+#             */
/*   Updated: 2025/08/01 20:16:53 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_if_should_split(t_token *toks)
{
	int	k;

	k = -1;
	while (toks->value[++k])
	{
		if ((toks->value[k] == '$' && !toks->value[k + 1])
			|| ft_strchr("\'\"=.", toks->value[k]))
			toks->strip = 2;
	}
}

char	*remove_outer_quotes(char *s)
{
	char	*result;
	int		i;
	int		j;
	char	quote_type;

	if (!s)
		return (NULL);
	result = malloc(ft_strlen(s) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;	
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			quote_type = s[i];
			i++;
			while (s[i] && s[i] != quote_type)
				result[j++] = s[i++];
			if (s[i] == quote_type)
				i++;
		}
		else
			result[j++] = s[i++];
	}	
	result[j] = '\0';
	return (result);
}

void	ft_lstadd_front(t_cmd_exec **lst, t_cmd_exec *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}
