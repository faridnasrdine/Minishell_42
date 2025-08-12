/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:08:00 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/12 18:31:42 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	dups_outs(t_cmd *tmp)
{
	if (tmp->std_out != 1)
	{
		tmp->std_out_dup1 = dup(1);
		dup2(tmp->std_out, 1);
		close(tmp->std_out);
		if (tmp->pipe_out)
			close(tmp->pipe_out);
	}
	else if (tmp->pipe_out)
	{
		tmp->std_out_dup1 = dup(1);
		dup2(tmp->pipe_out, 1);
		close(tmp->pipe_out);
	}
}

void	dups(t_cmd *tmp)
{
	if (tmp->std_in)
	{
		tmp->std_in_dup1 = dup(0);
		dup2(tmp->std_in, 0);
		close(tmp->std_in);
		if (tmp->pipe_in != 0)
			close(tmp->pipe_in);
	}
	else if (tmp->pipe_in)
	{
		tmp->std_in_dup1 = dup(0);
		dup2(tmp->pipe_in, 0);
		close(tmp->pipe_in);
	}
	dups_outs(tmp);
}

void	restore_std_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}
