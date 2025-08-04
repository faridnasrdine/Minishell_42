/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:01:46 by houssam           #+#    #+#             */
/*   Updated: 2025/08/04 19:19:41 by houssam          ###   ########.fr       */
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
		tmp->std_out = 1;
		if (tmp->pipe_out)
		{
			close(tmp->pipe_out);
			tmp->pipe_out = 0;
		}
	}
	else if (tmp->pipe_out)
	{
		tmp->std_out_dup1 = dup(1);
		dup2(tmp->pipe_out, 1);
		close(tmp->pipe_out);
		tmp->pipe_out = 0;
	}
}

void	dups(t_cmd *tmp)
{
	if (tmp->std_in)
	{
		tmp->std_in_dup1 = dup(0);
		dup2(tmp->std_in, 0);
		close(tmp->std_in);
		tmp->std_in = 0;
		if (tmp->pipe_in != 0)
		{
			close(tmp->pipe_in);
			tmp->pipe_in = 0;
		}
	}
	else if (tmp->pipe_in)
	{
		tmp->std_in_dup1 = dup(0);
		dup2(tmp->pipe_in, 0);
		close(tmp->pipe_in);
		tmp->pipe_in = 0;
	}
	dups_outs(tmp);
}

void	restore_std_fds(t_cmd *tmp)
{
	if (tmp->std_in_dup1 != -1)
	{
		dup2(tmp->std_in_dup1, 0);
		close(tmp->std_in_dup1);
		tmp->std_in_dup1 = -1;
	}
	if (tmp->std_out_dup1 != -1)
	{
		dup2(tmp->std_out_dup1, 1);
		close(tmp->std_out_dup1);
		tmp->std_out_dup1 = -1;
	}
	if (tmp->pipe_in)
	{
		close(tmp->pipe_in);
		tmp->pipe_in = 0;
	}
	if (tmp->pipe_out)
	{
		close(tmp->pipe_out);
		tmp->pipe_in = 0;
	}
}
