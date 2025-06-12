/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:56:55 by nafarid           #+#    #+#             */
/*   Updated: 2025/06/12 13:53:46 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int is_not_identifier(char *str)
{
    int i;
    if(!str || !*str)
        return 1;
    if(!ft_isalpha(str[0]) && str[0] != '_')
        return 1;
    i = 1;
    while(str[i])
    {
        if(!ft_isalnum(str[i]) && str[i] != '_')
            return 1;
        i++;
    }
    return 0;
}
char **ft_remove_env(char **envp, char *var)
{
    int len;
    char **new_env;
    int len_var;
    int i;
    int j;

    i = 0;
    j = 0;
    len_var = ft_strlen(var);
    len = cnt_string(envp);
    new_env = malloc(sizeof(char *) * (len + 1));
    if(!new_env)
        return NULL;
    while(envp[i])
    {
        if(ft_strcmp(envp[i], var) == 0 || (envp[i][len_var] != '=' && envp[i][len] != '\0'))
        {
            new_env[j++] = ft_strdup(envp[i]);
        }
        i++;
    }
    new_env[j] = NULL;
    return new_env;
}
int unset_cmd(char **av, t_data *data)
{
    int len;
    int i;
    char **new_env;

    i = 1;
    len = cnt_string(av);
    if(len == 1)
        return 0;
    while(av[i])
    {
        if(is_not_identifier(av[i]))
        {
             printf("Minishell: unset: %s: is not identifier\n", av[i]);
            data->exit_status = 1;
        }
        else
        {
            new_env = ft_remove_env(data->envp, av[i]);
            if(new_env)
            {
                free_string(data->envp);
                data->envp = new_env;
            }
        }
        i++;
    } 
    return data->exit_status;
}
