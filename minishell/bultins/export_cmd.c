/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:51:26 by houssam           #+#    #+#             */
/*   Updated: 2025/06/26 21:51:27 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	print_env(t_cmd_exec **env_lst)
{
	int		i;
	char	**envp;

	i = -1;
	envp = env_lst_to_arr(*env_lst, 'x', 1);
	while (envp[++i])
	{
		ft_putstr_fd("declere -x ", 1);
		ft_putstr_fd(envp[i], 1);
		ft_putchar_fd('\n', 1);
	}
	if (!envp[i])
	{
		arr_free(envp);
		change_stat(env_lst, 0);
		return (0);
	}
	else
	{
		arr_free(envp);
		change_stat(env_lst, 1);
		return (2);
	}
}

static t_cmd_exec	*env_var_update(t_cmd_exec **env_lst, char *before_eql,
		char *after_eql, char meaning)
{
	t_cmd_exec	*tmp;

	tmp = *env_lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, before_eql, ft_strlen(tmp->name) + 1) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(after_eql);
			tmp->meaning = meaning;
			break ;
		}
		tmp = tmp->next;
	}
	return (tmp);
}

static void	export_new(t_cmd_exec **env_lst, char *before_eql, char *after_eql,
		char meaning)
{
	char		*name;
	char		*value;
	t_cmd_exec	*node;
	t_cmd_exec	*tmp;

	tmp = env_var_update(env_lst, before_eql, after_eql, meaning);
	if (!tmp)
	{
		name = ft_strdup(before_eql);
		value = ft_strdup(after_eql);
		node = lst_new_ele(name, value);
		node->meaning = meaning;
		node->next = NULL;
		ft_lstadd_back(env_lst, node);
	}
}

static int	export_arg(t_cmd *cmd, int i, int *res, t_cmd_exec **env_lst)
{
	char	*eql;

	if (cmd->args[i][0] != '=' && ft_strchr(cmd->args[i], '='))
	{
		eql = ft_strchr(cmd->args[i], '=');
		*eql = '\0';
		if (check_var_name(cmd->args[i], res, env_lst) == 1)
			return (1);
		export_new(env_lst, cmd->args[i], eql + 1, 'e');
	}
	else
	{
		if (check_var_name(cmd->args[i], res, env_lst) == 1)
			return (1);
		export_new(env_lst, cmd->args[i], "", 'x');
	}
	return (0);
}

int	ft_export(t_cmd *cmd, t_cmd_exec **env_lst)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (!cmd->args[1])
		return (print_env(env_lst));
	else
	{
		while (cmd->args[++i])
			export_arg(cmd, i, &res, env_lst);
		if (!res)
			change_stat(env_lst, 0);
		else
			change_stat(env_lst, 1);
		return (0);
	}
}
