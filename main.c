/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:08:36 by aoussama          #+#    #+#             */
/*   Updated: 2025/06/10 07:56:22 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char **copy_env(char **env)
{
    int len;
    char **new_env;
    int i;

    i = 0;
    len = cnt_string(env);
    new_env = malloc(sizeof(char *) * len +1);
    if(!new_env)
        return NULL;
    while(i < len)
    {
        new_env[i] = ft_strdup(env[i]);
        i++;
    }
    new_env[len] = NULL;
    return new_env;
}
void int_data(t_data *data, char **envp)
{
    data->cdm_list = NULL;
    data->cmd_exec = NULL;
    data->envp = copy_env(envp);
    data->exit_status = 0;
}
int main(int ac, char **av, char **envp)
{
    char *cmd;
    t_data data;
    (void)ac;
    (void)av;

    int_data(&data, envp);
    while (1)
    {
        cmd = readline("<minishell> ");
        if (!cmd)
        {
            printf("exit\n");
            break;
        }
        if (*cmd)
        {
            add_history(cmd);
            data.cdm_list = paring_cmd(cmd);
            if(data.cdm_list)
            {
                execute_command(&data);
                ft_lstclear(&data.cdm_list);
            }  
        }
        free(cmd);
    }
    return data.exit_status;
}

