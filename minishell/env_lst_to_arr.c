/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_to_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:12:11 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/07 20:12:12 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_size(t_cmd_exec *lst, char meaning)
{
	int	count;

	count = 0;
	while (lst)
	{
		if ((meaning == 'x' && (lst->meaning == 'e' || lst->meaning == 'x'
					|| lst->meaning == 'q')) || (meaning == 'e'
				&& lst->meaning == 'e'))
			count++;
		lst = lst->next;
	}
	return (count);
}

static void	ft_empty(t_cmd_exec *env_lst, int *i, char **arr)
{
	char	*tmp1;
	char	*tmp2;

	if (env_lst->meaning == 'e')
	{
		tmp1 = ft_strdup(env_lst->name);
		tmp2 = ft_strdup("=\"\"");
		arr[*i] = ft_strjoin(tmp1, tmp2);
	}
	else
		arr[*i] = ft_strdup(env_lst->name);
}

static void	find_and_join(t_cmd_exec *env_lst, int quote, char **arr, int *i)
{
	char	*tmp;

	if (quote == 1)
	{
		if (ft_strncmp(env_lst->value, "", ft_strlen(env_lst->value))
			|| env_lst->meaning == 'q')
		{
			tmp = ft_strjoin(env_lst->name, "=\"");
			arr[*i] = ft_strjoin(tmp, env_lst->value);
			tmp = arr[*i];
			arr[*i] = ft_strjoin(tmp, "\"");
		}
		else
			ft_empty(env_lst, i, arr);
		*i = *i + 1;
	}
	else
	{
		arr[*i] = ft_strjoin_sep(env_lst->name, env_lst->value, '=');
		*i = *i + 1;
	}
}

char	**env_lst_to_arr(t_cmd_exec *env_lst, char meaning, int quote)
{
	int		size;
	int		i;
	char	**arr;

	i = 0;
	size = ft_size(env_lst, meaning);
	arr = ft_malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	arr[size] = NULL;
	while (env_lst)
	{
		if ((meaning == 'x' && (env_lst->meaning == 'e'
					|| env_lst->meaning == 'x' || env_lst->meaning == 'q'))
			|| (meaning == 'e' && env_lst->meaning == 'e'))
			find_and_join(env_lst, quote, arr, &i);
		env_lst = env_lst->next;
	}
	return (arr);
}
