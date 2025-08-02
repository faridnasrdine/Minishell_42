/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:52:23 by houssam           #+#    #+#             */
/*   Updated: 2025/08/02 09:04:19 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quote_del(t_token *toks)
{
	int		i;
	char	*new_value;
	char	*new_quote;

	i = -1;
	while (toks->value[++i])
	{
		if ((toks->value[i] == '\'' || toks->value[i] == '\"')
			&& toks->quote[i] == '1')
		{
			toks->value[i] = '\0';
			new_value = ft_strjoin(toks->value, toks->value + i + 1);
			toks->value = new_value;
			toks->quote[i] = '\0';
			new_quote = ft_strjoin(toks->quote, toks->quote + i + 1);
			toks->quote = new_quote;
			--i;
			if (toks->type == 'h')
				toks->type = 'H';
		}
	}
}
