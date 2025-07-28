/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:50:50 by houssam           #+#    #+#             */
/*   Updated: 2025/06/26 21:50:52 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	find_and_del(t_cmd *cmd, t_cmd_exec **env_lst, int i)
{
	t_cmd_exec	*tmp1;
	t_cmd_exec	*tmp2;

	tmp1 = *env_lst;
	while (tmp1)
	{
		if (tmp1->next && !ft_strncmp(cmd->args[i], tmp1->next->name,
				ft_strlen(cmd->args[i]) + 1))
		{
			tmp2 = tmp1->next;
			if (tmp1->next->next)
				tmp1->next = tmp1->next->next;
			else
				tmp1->next = NULL;
			lst_del(tmp2, &free);
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

static void	unset_vars(t_cmd *cmd, t_cmd_exec **env_lst, int *res)
{
	t_cmd_exec	*tmp;
	int			i;

	i = 0;
	while (cmd->args[++i])
	{
		if (!check_var_name(cmd->args[i], res, env_lst))
		{
			if (!ft_strncmp(cmd->args[i], "PWD", 4))
				pwd_fake(*env_lst);
			else if (!ft_strncmp(cmd->args[i], (*env_lst)->name,
					ft_strlen(cmd->args[i]) + 1))
			{
				tmp = *env_lst;
				*env_lst = (*env_lst)->next;
				lst_del(tmp, &free);
				continue ;
			}
			else
				find_and_del(cmd, env_lst, i);
		}
	}
}

int	unset(t_cmd *cmd, t_cmd_exec **env_lst)
{
	int	res;

	res = 0;
	if (env_lst && cmd != NULL)
	{
		if (!cmd->args[1])
			change_stat(env_lst, 0);
		else
			unset_vars(cmd, env_lst, &res);
	}
	if (!res)
		change_stat(env_lst, 0);
	else
		change_stat(env_lst, 1);
	return (0);
}
