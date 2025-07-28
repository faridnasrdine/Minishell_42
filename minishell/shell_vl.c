/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_vl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:34:37 by houssam           #+#    #+#             */
/*   Updated: 2025/07/26 06:46:08 by houssam          ###   ########.fr       */
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
	free(suffix);
	new_val = ft_strjoin(prefix, value);
	free(prefix);
	free(value);
	value = ft_strjoin(new_val, clean_suffix);
	free(new_val);
	free(clean_suffix);
	free(toks->value);
	toks->value = value;
	check_if_should_split(toks);
}

char	*erase_spaces(char *str)
{
	int		i;
	int		j;
	int		space;
	char	*res;

	res = malloc(ft_strlen(str) + 1);
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

static long	ft_new_atoi(const char *str, int *lvl)
{
	long			res;
	int				sign;
	unsigned int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	*lvl = res * sign;
	if (str[i])
		return (0);
	else
		return (1);
}

static void	shell_up(int lvl, t_cmd_exec *tmp, char *str)
{
	if (lvl < 0)
		lvl = 0;
	else if (lvl >= 0 && lvl <= 999)
		lvl++;
	else
	{
		ft_putstr_fd("Minishell: warning: shell level (", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(") too high, resetting to 1\n", 2);
		lvl = 1;
	}
	if (lvl == 1000)
	{
		free(tmp->value);
		tmp->value = ft_strdup("");
	}
	else
	{
		free(tmp->value);
		tmp->value = ft_itoa(lvl);
	}
}

void	shell_vl(t_cmd_exec **env_lst)
{
	t_cmd_exec	*new_ele;
	t_cmd_exec	*tmp;
	int			lvl;

	tmp = *env_lst;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "SHLVL", ft_strlen(tmp->name)))
		{
			if (ft_new_atoi(tmp->value, &lvl) == 0)
				lvl = 1;
			shell_up(lvl, tmp, tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
	{
		new_ele = lst_new_ele(ft_strdup("SHLVL"), ft_strdup("1"));
		ft_lstadd_back(env_lst, new_ele);
	}
}
