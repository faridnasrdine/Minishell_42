/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:39:47 by houssam           #+#    #+#             */
/*   Updated: 2025/07/17 06:21:43 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exit_stat_corr(long res)
{
	long double	num;
	long		int_part;

	if (res >= 0 && res <= 256)
		return (res);
	num = (long double)res / 256;
	int_part = (long)num;
	num = (num - int_part) * 256;
	if (num >= ((long)num + 0.5))
		res = (long)num + 1;
	else
		res = (long)num;
	if (res < 0)
		return (256 + res);
	else
		return (res);
}

static int	parsing_code(t_cmd *cmd, int *k)
{
	long	res;
	int		i;

	i = -1;
	while (cmd->args[1][++i])
		if (!(ft_isdigit(cmd->args[1][i]) == 1 || (!i && cmd->args[1][i] == '-')
				|| (!i && cmd->args[1][i] == '+')))
			break ;
	if (cmd->args[1][i] == '\0')
	{
		res = ft_atoi(cmd->args[1], k);
		res = exit_stat_corr(res);
	}
	else
	{
		*k = 1;
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("Minishell: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": numeric arg required\n", 2);
		res = 2;
	}
	return (res);
}

static void	run_exit(t_cmd_exec *env_lst)
{
	while (env_lst->meaning != '?')
		env_lst = env_lst->next;
	if (env_lst->value)
		free(env_lst->value);
	env_lst->value = ft_strdup("exit");
}

int	ft_exit(t_cmd *cmd, t_cmd_exec **env_lst)
{
	int	res;
	int	k;

	k = 0;
	if (cmd->args[1])
	{
		res = parsing_code(cmd, &k);
		if (!cmd->args[2] && !k)
			ft_putstr_fd("exit\n", 1);
		if (cmd->args[2] && !k)
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("Minishell: exit: too many args\n", 2);
			change_stat(env_lst, 1);
			return (2);
		}
		change_stat(env_lst, res);
		run_exit(*env_lst);
	}
	else
		run_exit(*env_lst);
	return (0);
}
