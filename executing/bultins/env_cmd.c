/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:56:24 by nafarid           #+#    #+#             */
/*   Updated: 2025/06/11 15:07:31 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void print_env(char **envp)
{
    char **env;
    int i;

	if(!envp)
		return;
	i = 0;
	env = envp;
    while(env[i])
    {
        printf("%s\n",env[i]);
        i++;
    }
}

int env_cmd(char **av, char **envp)
{
    int len_args;

    len_args = cnt_string(av);
    if(len_args == 1)
    {
        print_env(envp);
        return 0;
    }
    return 0;

}
