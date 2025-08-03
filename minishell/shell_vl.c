/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_vl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:34:37 by houssam           #+#    #+#             */
/*   Updated: 2025/08/03 17:36:18 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_new_tok_val(t_token *toks, char *value, int i, int j)
{
	char	*prefix;
	char	*suffix;
	char	*clean_suffix;
	char	*new_val;

	prefix = ft_substr(toks->value, 0, i);
	suffix = ft_strdup(toks->value + j);
	clean_suffix = remove_outer_quotes(suffix);
	new_val = ft_strjoin(prefix, value);
	value = ft_strjoin(new_val, clean_suffix);
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

