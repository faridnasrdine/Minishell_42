/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:45:37 by nafarid           #+#    #+#             */
/*   Updated: 2025/05/31 13:44:18 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int cnt_string(char **str)
{
    int i;

    i = 0;
    if (!str)
        return 0;
    while (str[i])
        i++; 
    return i;
}

int ft_cd_home(void)
{
    char *home;
    
    home = getenv("HOME");
    if (!home)
    {
        printf("cd: HOME not set\n");
        return 1;
    }
    if (chdir(home) == -1)
    {
        perror("cd");
        return 1;
    }
    return 0;
}

int ft_cd_oldpwd(void)
{
    char *oldpwd;
    
    oldpwd = getenv("OLDPWD");
    if (!oldpwd)
    {
        printf("cd: OLDPWD not set\n");
        return 1;
    }
    if (chdir(oldpwd) == -1)
    {
        perror("cd");
        return 1;
    }
    return 0;
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

int cd_cmd(char **av)
{
    if (cnt_string(av) > 2)
    {
        printf("cd: too many arguments\n");
        return 1;
    }
    else if (!av[1] || ft_strcmp(av[1], "~") == 0)
    {
        return ft_cd_home();
    }
    else if (ft_strcmp(av[1], "-") == 0)
    {
        return ft_cd_oldpwd();
    }
    else 
    {
        return ft_cd_path(av[1]);
    }
    return 0;
}
