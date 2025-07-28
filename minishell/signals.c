/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:18:20 by houssam           #+#    #+#             */
/*   Updated: 2025/07/26 08:57:42 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_exit_code = 0;

static void	ft_sigint_ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	set_exit_code(130);
}

int	get_exit_code(void)
{
	return (g_exit_code);
}

void	set_exit_code(int code)
{
	g_exit_code = code;
}

static void	ft_handle_sigquit(int sig)
{
	(void)sig;
	rl_redisplay();
}

void	ft_signals(void)
{
	signal(SIGINT, ft_sigint_ctrl_c);
	signal(SIGQUIT, ft_handle_sigquit);
}
