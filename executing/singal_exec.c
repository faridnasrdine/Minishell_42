/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singal_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:28:55 by nafarid           #+#    #+#             */
/*   Updated: 2025/06/01 18:28:55 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int built_in(char *cmd)
{
    if(!cmd)
        return 0;
    if(!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
        || !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "export")
        || !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "pwd")
        || !ft_strcmp(cmd, "exit"))
        return 1;
    return 0;
}

char *find_paht(char *cmd)
{
    char *path_env;
    char **path;
    char *tmp;
    char *new_path;
    int i;
    if(!cmd || !*cmd)
        return NULL;
    if(ft_strchr(cmd, '/'))
    {
        if(access(cmd, X_OK) == 0)
            return ft_strdup(cmd); 
    }
    path_env = getenv("PATH");
    if(!path_env)
        return NULL;
    path = ft_split(path_env, ':');
    if(!path)
        return NULL;
    i = 0;
    while(path[i])
    {
        tmp = ft_strjoin(path[i], "/");
        new_path = ft_strjoin(tmp, cmd);
        free (tmp);
        if(access(new_path, X_OK) == 0)
        {
            free_string(path, NULL);
            return new_path;
        }
        free(new_path);
        i++;
    }
    return NULL;
}
int signal_exec(t_data *data)
{
   
    // int status;
    int pid;
    t_cmd_exec *cmd_exec;

    cmd_exec = create_cmd_exec(data->cdm_list);
    if (!cmd_exec || !cmd_exec->argv || !cmd_exec->argv[0])
        return 1;
    // printf("%s\n", cmd_exec->argv[0]);
    if(built_in(cmd_exec->argv[0]))
    {
        data->exit_status = execute_builtin(cmd_exec, data);
        return (data->exit_status);
    }
    cmd_exec->path = find_paht(cmd_exec->argv[0]);
    if(!cmd_exec->path)
    {
        printf("Minishell : command not found : %s\n", cmd_exec->argv[0]);
        clear_data(data);
        data->exit_status = 127;
        return 127;
    }
    pid = fork();
    if(pid == -1)
    {
        perror("fork");
        return 1;
    }
    else if(pid == 0)
    {
        if (execve(cmd_exec->path, &cmd_exec->argv[0], data->envp) == -1)
        {
            perror("execve failed");
            clear_data(data);
            return 126;
        }
    }
    else
        wait(NULL);
    return 0;
}

