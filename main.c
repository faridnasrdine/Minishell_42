/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:08:36 by aoussama          #+#    #+#             */
/*   Updated: 2025/05/22 22:55:56 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int ac, char **av, char **env)
{
    char *cmd;
    t_data data;
        
    data.cmd_list = NULL;
    data.cmd_exec = NULL;
    data.envp = cop_env(env);
    data.exit_status = 0;
    (void)ac;
    (void)av;
    while (1)
    {
        cmd = readline("minishell> ");
        if (!cmd)
        {
            printf("exit\n");
            break;
        }

        if (*cmd)
        {
            add_history(cmd);
            data.cmd_list = paring_cmd(cmd);
            
            if (data.cmd_list)
            {
                execute_command(&data);
                ft_lstclear(&data.cmd_list);
            }
        }
        free(cmd);
    }
    return (data.exit_status);
}

