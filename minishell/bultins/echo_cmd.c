/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:56:21 by nafarid           #+#    #+#             */
/*   Updated: 2025/07/21 09:08:15 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:56:21 by nafarid           #+#    #+#             */
/*   Updated: 2025/07/21 09:01:38 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_n_option(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

char	*remove_quotes(char *str)
{
	int	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '\'' && str[len - 1] == '\'') || (str[0] == '"'
				&& str[len - 1] == '"')))
	{
		return (ft_substr(str, 1, len - 2));
	}
	return (ft_strdup(str));
}

void	fun(t_cmd *cmd, int i)
{
	char	*rm_arg;

	rm_arg = remove_quotes(cmd->args[i]);
	if (rm_arg)
	{
		write(1, rm_arg, ft_strlen(rm_arg));
		free(rm_arg);
	}
	if (cmd->args[i + 1])
		write(1, " ", 1);
}

int	ft_echo(t_cmd *cmd, t_cmd_exec **env_lst)
{
	int	i;
	int	has_n_option;

	i = 1;
	has_n_option = 0;
	while (cmd->args[i] && is_n_option(cmd->args[i]))
	{
		has_n_option = 1;
		i++;
	}
	while (cmd->args[i])
	{
		fun(cmd, i);
		i++;
	}
	change_stat(env_lst, 0);
	if (!has_n_option)
		write(1, "\n", 1);
	return (0);
}
