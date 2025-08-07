/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:11:45 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/07 20:11:47 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	arg_delete_next(t_token **toks, t_token **tmp1, t_token **tmp2)
{
	if (*toks == *tmp1)
	{
		*toks = (*tmp1)->next;
		*tmp1 = NULL;
		*tmp1 = *toks;
	}
	else
	{
		(*tmp2)->next = (*tmp1)->next;
		*tmp1 = NULL;
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
	cmd->args = ft_malloc(sizeof(char *) * (count + 1));
	if (!cmd->args)
		return (-1);
	cmd->args[count] = 0;
	arg_to_arr(toks, cmd);
	return (0);
}
