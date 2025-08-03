/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_front.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:20:22 by houssam           #+#    #+#             */
/*   Updated: 2025/08/03 19:10:06 by houssam          ###   ########.fr       */
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
			|| ft_strchr("=.", toks->value[k])
			|| in_quotes)
			{
				toks->strip = 2;
				return ;
			}
	}
}

char	*remove_outer_quotes(char *s)
{
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (len >= 2 && ((s[0] == '"' && s[len - 1] == '"') || (s[0] == '\''
				&& s[len - 1] == '\'')))
		return (ft_substr(s, 1, len - 2));
	return (ft_strdup(s));
}

void	ft_lstadd_front(t_cmd_exec **lst, t_cmd_exec *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}
