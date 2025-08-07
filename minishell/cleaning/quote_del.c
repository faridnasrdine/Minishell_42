/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:06:27 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/07 20:18:59 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quote_del(t_token *toks)
{
	int		i;
	char	*new_value;
	char	*new_quote;

	i = -1;
	if (ft_strlen(toks->value) != ft_strlen(toks->quote))
		return ;
	while (toks->value[++i])
	{
		if ((toks->value[i] == '\'' || toks->value[i] == '\"')
			&& toks->quote[i] == '1')
		{
			toks->value[i] = '\0';
			new_value = ft_strjoin(toks->value, toks->value + i + 1);
			toks->quote[i] = '\0';
			new_quote = ft_strjoin(toks->quote, toks->quote + i + 1);
			if (!new_quote || !new_value)
				return ;
			toks->value = new_value;
			toks->quote = new_quote;
			if (toks->type == 'h')
				toks->type = 'H';
			i--;
		}
	}
}
