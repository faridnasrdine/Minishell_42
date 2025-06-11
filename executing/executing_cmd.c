/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:21:07 by nafarid           #+#    #+#             */
/*   Updated: 2025/05/11 13:21:07 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int execute_builtin(t_cmd_exec *cmd, t_data *data)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		print_echo(cmd->argv + 1);
	if (!ft_strcmp(cmd->argv[0], "cd"))
		cd_cmd(cmd->argv);
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		pwd_cmd();
	if (!ft_strcmp(cmd->argv[0], "exit"))
		exit_cmd(cmd->argv);
	if (!ft_strcmp(cmd->argv[0], "unset"))
		unset_cmd(cmd->argv);
	if (!ft_strcmp(cmd->argv[0], "export"))
		export_cmd(cmd->argv, &data->envp);
	if (!ft_strcmp(cmd->argv[0], "env"))
		env_cmd(cmd->argv, data->envp);
	return 0;
}
int execute_command(t_data *data)
{
	if (!data || !data->cdm_list)
		return 1;
	return (signal_exec(data));
}
