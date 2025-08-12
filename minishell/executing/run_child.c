/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:21:13 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/12 18:32:15 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	proc_handle_ctrl_c(int sig)
{
	(void)sig;
	exit(2);
}

static void	proc_handle_sigquit(int sig)
{
	(void)sig;
	exit(3);
}

static void	not_built(t_cmd_exec **env_lst, t_cmd *exec_cmd)
{
	char	**env;

	env = env_lst_to_arr(*env_lst, 'e', 0);
	check_if_dir(exec_cmd);
	if (!exec_cmd->path)
		exec_cmd->path = ft_strdup("");
	execve(exec_cmd->path, exec_cmd->args, env);
	if (exec_cmd->redir_error != 3)
	{
		perror("Minishell");
		free_grabage();
		exit(127);
	}
}

static void	fun(t_cmd *exec_cmd, int *exit_code)
{
	char	*tmp;

	if (exec_cmd->path_error == 4)
		*exit_code = 0;
	else if (!exec_cmd->path_error)
		*exit_code = 0;
	else if (exec_cmd->path_error == 2)
	{
		if (exec_cmd->args[0])
		{
			tmp = ft_strjoin("Minishell: ", (exec_cmd->args[0]));
			tmp = ft_strjoin(tmp, ": No such file or directory\n");
			ft_putstr_fd(tmp, 2);
			tmp = NULL;
		}
		*exit_code = 127;
	}
	else if (exec_cmd->args[0])
	{
		tmp = ft_strjoin("Minishell: ", (exec_cmd->args[0]));
		tmp = ft_strjoin(tmp, ": command not found\n");
		ft_putstr_fd(tmp, 2);
		tmp = NULL;
		*exit_code = 127;
	}
}

void	child_proc(t_cmd **cmd, t_cmd_exec **env_lst, int id)
{
	t_cmd	*exec_cmd;
	int		exit_code;

	signal(SIGINT, proc_handle_ctrl_c);
	signal(SIGQUIT, proc_handle_sigquit);
	exec_cmd = close_pipes(cmd, id);
	exec_cmd->path = find_cmd(exec_cmd, *env_lst);
	exit_code = 0;
	if (!exec_cmd->path)
	{
		fun(exec_cmd, &exit_code);
		restore_std_fds();
		free_grabage();
		exit(exit_code);
	}
	else if (exec_cmd->builtin != 1)
		not_built(env_lst, exec_cmd);
	else
	{
		exit_code = exec_run(exec_cmd, env_lst);
		restore_std_fds();
		free_grabage();
		exit(exit_code);
	}
}
