/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:21:07 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/04 03:35:24 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	waiting_helper(t_cmd_exec **env_lst, t_cmd **cmd, int *exit_stat,
		int *stat_code)
{
	int	sig;

	(void)cmd;
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

static void	waiting(t_cmd_exec **env_lst, t_cmd **cmd, int idx, int *pids)
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
				waiting_helper(env_lst, cmd, &exit_stat, &stat_code);
			else if (WIFEXITED(exit_stat))
			{
				stat_code = WEXITSTATUS(exit_stat);
				change_stat(env_lst, stat_code);
			}
		}
	}
	ft_signals();
}

static void	parent_proc(t_cmd **cmd, t_cmd_exec **env_lst, int idx, int *pids)
{
	t_cmd	*tmp;

	tmp = *cmd;
	while (tmp)
	{
		if (tmp->std_in != 0)
			close(tmp->std_in);
		if (tmp->std_out != 1)
			close(tmp->std_out);
		if (tmp->pipe_out != 0)
			close(tmp->pipe_out);
		if (tmp->pipe_in != 0)
			close(tmp->pipe_in);
		tmp = tmp->next;
	}
	waiting(env_lst, cmd, idx, pids);
}

static void	exec_in_process(t_cmd **cmd, t_cmd_exec **env_lst)
{
	int		my_pid;
	t_cmd	*tmp;
	t_cmd	*tmp2;
	pid_t	*pids;
	int		num_cmd;
	int		idx;

	tmp = *cmd;
	tmp2 = tmp;
	my_pid = 1;
	idx = 0;
	num_cmd = count_cmds(tmp);
	pids = ft_malloc(sizeof(pid_t) * num_cmd);
	if (!pids)
		exit(EXIT_FAILURE);
	while (tmp && my_pid != 0)
	{
		if (tmp->id == 0 || tmp2->pipe == 1)
			my_pid = fork();
		if (!my_pid)
			check_dir_exe(tmp, env_lst, cmd);
		else if (tmp && my_pid > 0)
		{
			pids[idx++] = my_pid;
			restore_std_fds(tmp);
			tmp2 = tmp;
			tmp = tmp->next;
		}
	}
	if (my_pid != 0)
		parent_proc(cmd, env_lst, idx, pids);
}

void	exec(t_cmd **cmd, t_cmd_exec **env_lst)
{
	(*cmd)->path = find_cmd(*cmd, *env_lst);
	if ((*cmd)->path && (*cmd)->builtin == 1 && (*cmd)->next == NULL)
		exec_built(*cmd, env_lst, 0);
	else
		exec_in_process(cmd, env_lst);
}
