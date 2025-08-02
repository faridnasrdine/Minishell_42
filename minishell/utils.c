/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:59:12 by houssam           #+#    #+#             */
/*   Updated: 2025/07/31 09:19:29 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_c_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	set_exit_code(130);
	close(0);
}

t_token	*new_ele_tok_node(char **words, int i)
{
	t_token	*curr;

	curr = malloc(sizeof(t_token));
	if (!curr)
		return (NULL);
	curr->type = 'w';
	curr->value = ft_strdup(words[i]);
	curr->quote = ft_strdup("0");
	curr->next = NULL;
	if (!curr->value || !curr->quote)
		return (NULL);
	return (curr);
}

static int	ft_split_token_into_nodes_2(t_token *curr, char **words,
		t_token *next)
{
	int		i;
	t_token	*new;

	i = 0;
	while (words[++i])
	{
		new = new_ele_tok_node(words, i);
		if (!new)
			return (-1);
		curr->next = new;
		curr = new;
	}
	curr->next = next;
	return (0);
}

int	split_token_into_nodes(t_token *tok)
{
	char	**words;
	t_token	*curr;
	t_token	*next;

	if (!tok || !tok->value || !tok->value[0])
		return (-1);
	curr = tok;
	next = tok->next;
	words = ft_split(tok->value, ' ');
	if (!words || !words[0])
		return (-1);
	free(curr->value);
	curr->value = ft_strdup(words[0]);
	free(curr->quote);
	curr->quote = ft_strdup("0");
	if (!curr->value || !curr->quote)
		return (-1);
	if (ft_split_token_into_nodes_2(curr, words, next) == -1)
		return (-1);
	arr_free(words);
	return (0);
}
