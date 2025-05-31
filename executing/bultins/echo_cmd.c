/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:56:21 by nafarid           #+#    #+#             */
/*   Updated: 2025/05/22 22:56:21 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int is_n_option(char *str)
{
    int i;

    if(!str || str[0] != '-'|| str[1] != 'n')
        return 0;
    i = 2;
    while(str[i])
    {
        if(str[i] != 'n')
            return 0;
        i++;
    }
    return 1;
}

char *remove_quotes(char *str)
{
    int len = ft_strlen(str);
    if((len >= 2 && str[0] == '\'' && str[len - 1] == '\'' )|| (str[0] == '"' && str[len - 1] == '"'))
    {
        return ft_substr(str, 1, len - 2);
    }
    return ft_strdup(str);
}

int print_echo(char **av)
{
    char *rm_arg;
    int i = 0;
    int j = 0;

    while(av[i] && is_n_option(av[i]))
    {
        j = 1;
        i++;
    }
    while(av[i])
    {
        rm_arg = remove_quotes(av[i]);
        if(rm_arg)
        {
            write(1, rm_arg, ft_strlen(rm_arg));
            free(rm_arg);
        }
        if(av[i + 1])
            write(1, " ", 1);
        i++;
    }
    if(!j)
        write(1, "\n", 1);
    return 0;
}

int execute_builtin(t_cmd_exec *cmd)
{
    if(!ft_strcmp(cmd->argv[0], "echo"))
        print_echo(cmd->argv + 1);
    if(!ft_strcmp(cmd->argv[0], "cd"))
        cd_cmd(cmd->argv);
    if(!ft_strcmp(cmd->argv[0], "pwd"))
        pwd_cmd();
    if(!ft_strcmp(cmd->argv[0], "exit"))
        exit_cmd(cmd->argv);
    if(!ft_strcmp(cmd->argv[0], "unset"))
        unset_cmd(cmd->argv);
    return 0;
}