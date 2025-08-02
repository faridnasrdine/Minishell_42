/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:19:02 by houssam           #+#    #+#             */
/*   Updated: 2025/08/01 15:12:25 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	arg_delete_next(t_token **toks, t_token **tmp1, t_token **tmp2)
{
	if (*toks == *tmp1)
	{
		*toks = (*tmp1)->next;
		lst_del_tok(*tmp1, &free);
		*tmp1 = *toks;
	}
	else
	{
		(*tmp2)->next = (*tmp1)->next;
		lst_del_tok(*tmp1, &free);
		*tmp1 = (*tmp2)->next;
	}
}

static void	arg_to_arr(t_token **toks, t_cmd *cmd)
{
	int		i;
	t_token	*tmp1;
	t_token	*tmp2;

	i = -1;
	tmp2 = *toks;
	tmp1 = *toks;
	while (tmp1 && tmp1->type != 'c')
	{
		if (tmp1->type == 'w')
		{
			cmd->args[++i] = ft_strdup(tmp1->value);
			if (tmp1->expanded)
				cmd->path_error = 4;
			arg_delete_next(toks, &tmp1, &tmp2);
		}
		else
		{
			tmp2 = tmp1;
			tmp1 = tmp1->next;
		}
	}
}

int	arg_count(t_token **toks, t_cmd *cmd)
{
	int		count;
	t_token	*tmp;

	tmp = *toks;
	count = 0;
	while (tmp && tmp->type != 'c')
	{
		if (tmp->type == 'r')
		{
			tmp = tmp->next;
			if (tmp && tmp->type == 'w')
				tmp->type = 'v';
		}
		else
			count++;
		if (tmp)
			tmp = tmp->next;
	}
	cmd->args = malloc(sizeof(char *) * (count + 1));
	if (!cmd->args)
		return (-1);
	cmd->args[count] = 0;
	arg_to_arr(toks, cmd);
	return (0);
}
