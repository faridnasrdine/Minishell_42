/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:07:43 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/08 14:06:15 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	find_and_del(t_cmd *cmd, t_cmd_exec **env_lst, int i)
{
	t_cmd_exec	*tmp1;

	tmp1 = *env_lst;
	while (tmp1)
	{
		if (tmp1->next && !ft_strncmp(cmd->args[i], tmp1->next->name,
				ft_strlen(cmd->args[i]) + 1))
		{
			if (tmp1->next->next)
				tmp1->next = tmp1->next->next;
			else
				tmp1->next = NULL;
		}
		else
			tmp1 = tmp1->next;
	}
}

static void	pwd_fake(t_cmd_exec *env_lst)
{
	while (env_lst)
	{
		if (!ft_strncmp(env_lst->name, "PWD", 4))
		{
			env_lst->meaning = 'p';
			break ;
		}
		env_lst = env_lst->next;
	}
}

static void	unset_vars(t_cmd *cmd, t_cmd_exec **env_lst)
{
	int	i;

	i = 0;
	while (cmd->args[++i])
	{
		if (!ft_strncmp(cmd->args[i], "PWD", 4))
			pwd_fake(*env_lst);
		else if (!ft_strncmp(cmd->args[i], (*env_lst)->name,
				ft_strlen(cmd->args[i]) + 1) && cmd->args[i][0] != '?')
		{
			*env_lst = (*env_lst)->next;
			continue ;
		}
		else
			find_and_del(cmd, env_lst, i);
	}
}

int	ft_unset(t_cmd *cmd, t_cmd_exec **env_lst)
{
	if (env_lst && cmd != NULL)
	{
		if (!cmd->args[1])
			change_stat(env_lst, 0);
		else
			unset_vars(cmd, env_lst);
	}
	change_stat(env_lst, 0);
	return (0);
}
