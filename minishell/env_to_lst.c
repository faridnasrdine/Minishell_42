/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:34:54 by houssam           #+#    #+#             */
/*   Updated: 2025/06/30 00:07:14 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd_exec	*env_content(char *before, char *after)
{
	char		*name;
	char		*value;
	t_cmd_exec	*node;

	name = ft_strdup(before);
	value = ft_strdup(after);
	node = lst_new_ele(name, value);
	node->next = NULL;
	return (node);
}

static int	exit_status(t_cmd_exec *node, t_cmd_exec **env_lst)
{
	char	*blank;

	blank = malloc(sizeof(char) * 2);
	if (!blank)
		return (0);
	blank[0] = '0';
	blank[1] = '\0';
	node = lst_new_ele(ft_strdup("?"), blank);
	node->meaning = '?';
	node->status = 0;
	ft_lstadd_front(env_lst, node);
	return (1);
}

int	env_to_lst(char **env, t_cmd_exec **env_lst)
{
	int			i;
	char		*line;
	t_cmd_exec	*node;

	i = 0;
	*env_lst = 0;
	while (env[i] != 0)
		i++;
	i = 0;
	while (env[i] != 0)
	{
		line = ft_strchr(env[i], '=');
		*line = '\0';
		node = env_content(env[i], line + 1);
		ft_lstadd_back(env_lst, node);
		i++;
	}
	return (exit_status(node, env_lst));
}
