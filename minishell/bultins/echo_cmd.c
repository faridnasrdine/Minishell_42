/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:56:21 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/02 18:38:54 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_flag(char *str, int *n)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (i == 0 && str[i] == '-')
			continue ;
		else if (i != 0 && str[i] == 'n')
			continue ;
		else
			break ;
	}
	if (i != 0 && str[i] == '\0')
	{
		*n = 1;
		return (1);
	}
	return (0);
}

static void	echo_print(t_cmd *command, int *i)
{
	int	flag;

	flag = 0;
	while (command->args[*i] != 0)
	{
		if (flag == 1)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(command->args[*i], 1);
		flag = 1;
		++(*i);
	}
}

int	ft_echo(t_cmd *command, t_cmd_exec **env_lst)
{
	int	n;
	int	i;

	n = 0;
	if (command->args[1] == 0)
		ft_putchar_fd('\n', 1);
	else
	{
		i = 0;
		while (command->args[++i] != 0 && check_flag(command->args[i], &n) == 1)
			;
		echo_print(command, &i);
		if (n == 0)
			ft_putchar_fd('\n', 1);
	}
	change_stat(env_lst, 0);
	return (0);
}

