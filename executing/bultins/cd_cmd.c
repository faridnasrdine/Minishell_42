/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:45:37 by nafarid           #+#    #+#             */
/*   Updated: 2025/06/13 20:51:47 by nafarid          ###   ########.fr       */
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
// void update_env(char **env, char *new_pwd, char *old_pwd)
// {
//     int i;
//     char **new_envp;
//     i = 0;
//     new_pwd = getenv("OLDPWD");
//     old_pwd = getenv("PWD");
//     new_envp = add_new_var(env, "PWD", new_pwd);
//     if (new_envp != env)
//     {
//         free_string(env);
//         env = new_envp;
//     }
// }
// int ft_cd_path(char *path)
// {
//     if (chdir(path) == -1)
//     {
//         printf("cd: %s: No such file or directory\n", path);
//         return 1;
//     }
//     return 0;
// }

// int cd_cmd(char **av, char ***env)
// {
//     char *new_pwd = NULL;
//     char *old_pwd = NULL;
//     int i;
    
//     if (cnt_string(av) > 2)
//     {
//         printf("cd: too many arguments\n");
//         i = 1;
//     }
//     else 
//     {
//         i = ft_cd_path(av[1]);
//         update_env(*env, new_pwd, old_pwd);
//     }
//     return 0;
// }
int cd_cmd(char **av, char ***envp)
{
    char *target;
    char *pwd;
    char *oldpwd;
    char **new_envp;

    if (!av[1])
    {
        target = getenv("HOME");
        if (!target)
        {
            printf("minishell: cd: HOME not set\n");
            return 1;
        }
    }
    else if (av[2])
    {
        printf("minishell: cd: too many arguments\n");
        return 1;
    }
    else
        target = av[1];
    oldpwd = getcwd(NULL, 0);
    if (!oldpwd)
    {
        printf("minishell: cd: error getting current directory\n");
        return 1;
    }
    if (chdir(target) == -1)
    {
        perror("minishell: cd");
        return 1;
    }

    pwd = getcwd(NULL, 0);
    if (!pwd)
    {
        printf("minishell: cd: error getting current directory\n");
        return 1;
    }

    new_envp = add_new_var(*envp, "PWD", pwd);
    if (new_envp != *envp)
    {
        free_string(*envp);
        *envp = new_envp;
    }
    new_envp = add_new_var(*envp, "OLDPWD", oldpwd);
    if (new_envp != *envp)
    {
        free_string(*envp);
        *envp = new_envp;
    }

    free(pwd);
    free(oldpwd);
    return 0;
}
