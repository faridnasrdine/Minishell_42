/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:34:18 by houssam           #+#    #+#             */
/*   Updated: 2025/06/26 20:34:20 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	split_ifs(t_token *tmp, char *ifs, int *i)
{
	char	*new_str;
	t_token	*new_ele;
	int		j;

	j = *i;
	tmp->value[*i] = '\0';
	tmp->quote[*i] = '\0';
	while (ft_strchr(ifs, tmp->value[++j]) && tmp->value[j])
		;
	new_ele = lst_new_ele_tok('w', ft_strdup(&(tmp->value[j])));
	new_ele->quote = ft_strdup(&(tmp->quote[j]));
	new_ele->next = tmp->next;
	tmp->next = new_ele;
	new_str = ft_strdup(tmp->value);
	free(tmp->value);
	tmp->value = new_str;
	new_str = ft_strdup(tmp->quote);
	free(tmp->quote);
	tmp->quote = new_str;
	return (1);
}

static void	search_ifs(t_token **toks, char *ifs)
{
	t_token	*tmp;
	int		i;

	tmp = *toks;
	while (tmp && tmp->type != 'c')
	{
		i = -1;
		if (tmp->type != 'r' && tmp->type != 'h')
		{
			while (tmp->value[++i])
			{
				if (tmp->value[i] == '\'' && tmp->quote[i] == '1')
					while (!(tmp->value[++i] == '\'' && tmp->quote[i] == '1'))
						;
				else if (tmp->value[i] == '\"' && tmp->quote[i] == '1')
					while (!(tmp->value[++i] == '\"' && tmp->quote[i] == '1'))
						;
				else if (ft_strchr(ifs, tmp->value[i]) && tmp->quote[i] == '2'
					&& split_ifs(tmp, ifs, &i))
					break ;
			}
		}
		tmp = tmp->next;
	}
}

void	word_split(t_token **toks, t_cmd_exec *env_lst)
{
	while (env_lst != NULL)
	{
		if (!ft_strncmp(env_lst->name, "IFS", 4))
			break ;
		env_lst = env_lst->next;
	}
	if (env_lst)
		search_ifs(toks, env_lst->value);
}
