/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:21:07 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/10 14:36:55 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	waiting_helper(t_cmd_exec **env_lst, int *exit_stat, int *stat_code)
{
	int	sig;

	sig = WTERMSIG(*exit_stat);
	if (sig == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
		*stat_code = sig + 128;
		change_stat(env_lst, *stat_code);
	}
	else
	{
		if (sig == SIGINT)
			ft_putchar_fd('\n', 1);
		*stat_code = sig + 128;
		change_stat(env_lst, *stat_code);
	}
}

void	waiting(t_cmd_exec **env_lst, int idx, int *pids)
{
	int	exit_stat;
	int	stat_code;
	int	i;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	i = -1;
	while (++i < idx)
	{
		waitpid(pids[i], &exit_stat, 0);
		if (i == idx - 1)
		{
			if (WIFSIGNALED(exit_stat) != 0)
				waiting_helper(env_lst, &exit_stat, &stat_code);
			else if (WIFEXITED(exit_stat))
			{
				stat_code = WEXITSTATUS(exit_stat);
				change_stat(env_lst, stat_code);
			}
		}
	}
	ft_signals();
}

static int	fork_and_execute(t_cmd **cmd, t_cmd_exec **env_lst, pid_t *pids)
{
	int		my_pid;
	t_cmd	*tmp;
	t_cmd	*tmp2;
	int		idx;

	tmp = *cmd;
	tmp2 = tmp;
	my_pid = 1;
	idx = 0;
	while (tmp && my_pid != 0)
	{
		if (tmp->id == 0 || tmp2->pipe == 1)
			my_pid = fork();
		if (!my_pid)
			check_dir_exe(tmp, env_lst, cmd);
		else if (tmp && my_pid > 0)
		{
			pids[idx++] = my_pid;
			tmp2 = tmp;
			tmp = tmp->next;
		}
	}
	return (idx);
}

static void	exec_in_process(t_cmd **cmd, t_cmd_exec **env_lst)
{
	pid_t	*pids;
	int		process_count;

	pids = allocate_pid_array(*cmd);
	process_count = fork_and_execute(cmd, env_lst, pids);
	parent_proc(env_lst, process_count, pids);
}

void	exec(t_cmd **cmd, t_cmd_exec **env_lst)
{
	(*cmd)->path = find_cmd(*cmd, *env_lst);
	if ((*cmd)->path && (*cmd)->builtin == 1 && (*cmd)->next == NULL)
		exec_built(*cmd, env_lst, 0);
	else
		exec_in_process(cmd, env_lst);
}
