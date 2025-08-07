/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:10:34 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/07 20:10:37 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	opers(t_token *toks, t_cmd_exec **env_lst)
{
	t_token	*prev;

	prev = toks;
	while (toks)
	{
		if (toks->type == 'o')
		{
			if (ft_strncmp(toks->value, ">", 2) == 0 || ft_strncmp(toks->value,
					">>", 3) == 0 || ft_strncmp(toks->value, "<", 2) == 0
				|| ft_strncmp(toks->value, "<<", 3) == 0)
				toks->type = 'r';
			else if (prev->type == 'w' && !ft_strncmp(toks->value, "|", 2)
				&& toks->next)
				toks->type = 'c';
			else
			{
				ft_putstr_fd("Minishell: Syntax error: unexpected token '", 2);
				ft_putstr_fd(toks->value, 2);
				return (ft_putstr_fd("'\n", 2), change_stat(env_lst, 2), -1);
			}
		}
		prev = toks;
		toks = toks->next;
	}
	return (0);
}

int	parsing_line(char *line, t_token **toks, t_cmd_exec **env_lst)
{
	int		count;
	char	chars[11];
	t_cmd	*cmd;

	cmd = NULL;
	*toks = NULL;
	ft_strlcpy(chars, "<>| \t\n", 11);
	count = tokens_count(line, chars);
	if (count > 0)
	{
		toks_arr(line, chars, toks);
		if (opers(*toks, env_lst) == -1)
			return (-1);
		if (toks_to_struct(toks, &cmd, env_lst) == 0)
			exec(&cmd, env_lst);
	}
	else if (count < 0)
		change_stat(env_lst, 2);
	return (1);
}
