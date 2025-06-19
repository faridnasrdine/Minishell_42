/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:56:24 by nafarid           #+#    #+#             */
/*   Updated: 2025/06/15 09:34:43 by nafarid          ###   ########.fr       */
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
        if(ft_strchr(env[i], '='))
            printf("%s\n",env[i]);
        i++;
    }
}
// int pars_env(char **av, char **envp)
// {
//     int i;
//     int bol;
    
//     i = 1;
//     bol = 0;
//     while(av[i])
//     {
//         if(ft_strcmp(av[i], "env") != 0)
//         {
//             bol = 1;
//             break;
//         }
//         i++;
//     }
//     if(bol)
//     {
//         printf("Minishell: env: %s: No such file or directory\n", av[i]);
//         return 127;
//     }
//     else
//         print_env(envp);
//     return 0;
// }

int exe_wiht_env(char **av, char **envp)
{
    char *path;
    int id;
    
    path = find_paht(av[1]);
    if(!path)
    {
        printf("env: '%s': No such file or directory\n", av[1]);
        return 127;
    }
    id = fork();
    if(id == -1)
    {
        perror("fork");
        free(path);
        return 1;
    }
    else if(id == 0)
    {
        if(execve(path, &av[1], envp) == -1)
        {
            perror("execve");
            return (126);
        }
    }
    else
    {
        wait(NULL);
        free(path);
    }
        
    return 0;
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
    else
    {
        return(exe_wiht_env(av, envp));
    }
    return 0;

}
