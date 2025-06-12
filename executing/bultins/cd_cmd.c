/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:45:37 by nafarid           #+#    #+#             */
/*   Updated: 2025/06/12 17:16:45 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


// int ft_cd_home(char *new_pwd, char *old_pwd, t_data *data)
// {
//     char *home;
    
//     home = getenv("HOME");
//     if (!home)
//     {
//         printf("cd: HOME not set\n");
//         return 1;
//     }
//     if (chdir(home) == -1)
//     {
//         perror("cd");
//         return 1;
//     }
//     new_pwd = home;
//     old_pwd = getenv("PWD");
//     add_new_var(data->envp, "PWD", new_pwd);
//     return 0;
// }

// int ft_cd_oldpwd(void)
// {
//     char *oldpwd;
    
//     oldpwd = getenv("OLDPWD");
//     if (!oldpwd)
//     {
//         printf("cd: OLDPWD not set\n");
//         return 1;
//     }
//     if (chdir(oldpwd) == -1)
//     {
//         perror("cd");
//         return 1;
//     }
//     return 0;
// }
void update_env(char **env, char *new_pwd, char *old_pwd)
{
    int i;

    i = 0;
    new_pwd = ft_strjoin("PWD",getenv("OLDPWD"));
    old_pwd = ft_strjoin("OLDPWD=",getenv("PWD"));
    while(env[i])
    {
        if(ft_strcmp(env[i], new_pwd) == 0)
            env[i] = new_pwd;
        i++;
    }
}
int ft_cd_path(char *path)
{
    if (chdir(path) == -1)
    {
        printf("cd: %s: No such file or directory\n", path);
        return 1;
    }
    return 0;
}

int cd_cmd(char **av, t_data *data)
{
    char *new_pwd = NULL;
    char *old_pwd = NULL;
    
    if (cnt_string(av) > 2)
    {
        printf("cd: too many arguments\n");
        return 1;
    }
    else 
    {
        data->exit_status = ft_cd_path(av[1]);
        update_env(data->envp, new_pwd, old_pwd);
    }
    return data->exit_status;
}
