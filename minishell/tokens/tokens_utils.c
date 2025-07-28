/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:55:55 by houssam           #+#    #+#             */
/*   Updated: 2025/07/24 15:28:55 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	word_alloc(t_token **toks, int *j, size_t *word_len, char *line)
{
	t_token	*tok_ele;
	char	*str;

	if (line && *word_len != 0)
	{
		str = malloc(sizeof(char) * (*word_len + 1));
		if (!str || !line)
			return ;
		ft_strlcpy(str, line, *word_len + 1);
		if (ft_strchr("<>|&;() \t\n", str[0]))
			tok_ele = lst_new_ele_tok('o', str);
		else
			tok_ele = lst_new_ele_tok('w', str);
		lstadd_back_tok(toks, tok_ele);
		(*j)++;
		line = NULL;
		*word_len = 0;
	}
}

static char	*single_quotes(char *line, int *i, size_t *word, char *chars)
{
	if (line[*i] == '\'')
	{
		(*word)++;
		(*i)++;
		while (line[*i] != '\'' && line[*i] != '\0')
		{
			(*word)++;
			(*i)++;
		}
		(*word)++;
		(*i)++;
		if (line[*i] == '\0' || ft_strchr(chars, line[*i]))
			return (line + *i - *word);
	}
	return (NULL);
}

static char	*double_quotes(char *line, int *i, size_t *word, char *chars)
{
	if (line[*i] == '\"')
	{
		(*word)++;
		(*i)++;
		while (line[*i] != '\"' && line[*i])
		{
			(*word)++;
			(*i)++;
		}
		(*word)++;
		(*i)++;
		if (line[*i] == '\0' || ft_strchr(chars, line[*i]))
			return (line + *i - *word);
	}
	return (NULL);
}

static char	*words_and_opers(char *line, int *i, size_t *word, char *chars)
{
	if (ft_strchr(chars, line[*i]) && line[*i] != '\0')
	{
		while (ft_strchr(chars, line[*i]) && line[*i] != '\0')
		{
			(*word)++;
			(*i)++;
		}
		return (line + *i - *word);
	}
	else if (line[*i] != '\'' && line[*i] != '\"' && line[*i])
	{
		while (ft_strchr(chars, line[*i]) == 0 && line[*i] && line[*i] != '\''
			&& line[*i] != '\"')
		{
			(*word)++;
			(*i)++;
		}
		if ((line[*i] != '\'' && line[*i] != '\"') || line[*i] == '\0')
			return (line + *i - *word);
	}
	return (NULL);
}

void	toks_arr(char *line, char *chars, t_token **toks)
{
	int		i;
	int		j;
	size_t	word_len;
	char	*start;

	i = 0;
	j = 0;
	word_len = 0;
	while (line[i])
	{
		start = single_quotes(line, &i, &word_len, chars);
		word_alloc(toks, &j, &word_len, start);
		start = double_quotes(line, &i, &word_len, chars);
		word_alloc(toks, &j, &word_len, start);
		start = words_and_opers(line, &i, &word_len, chars);
		word_alloc(toks, &j, &word_len, start);
	}
	toks_trim(toks);
}
