/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_cmd_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:21:04 by nafarid           #+#    #+#             */
/*   Updated: 2025/05/11 13:21:04 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char **get_cmd(char *str)
{
    char **cmd;
    int i = 0;
    char *temp = NULL;

    // Avoid using strlen for an array that could have memory issues.
    cmd = malloc(sizeof(char *) * 2); // Just one cmd + NULL terminator
    if (!cmd)
        return NULL;

    // Skip leading spaces.
    while (str[i] == ' ')
        i++;

    // Now check for the next word (command).
    temp = strdup(str + i);
    cmd[0] = temp;
    cmd[1] = NULL;
    return cmd;
}

int check_cmd(char *cmd)
{
    if (strcmp("cd", cmd) == 0 || strcmp("echo", cmd) == 0 || strcmp("env", cmd) == 0 || strcmp("pwd", cmd) == 0 || strcmp("unset", cmd) == 0 || strcmp("export", cmd) == 0 || strcmp("exit", cmd) == 0)
        return 1;
    return 0;
}

char **exec_dir(t_shell *shell, int i)
{
    char **path = NULL;
    char *tmp = NULL;

    tmp = get_path(shell, i);
    if (!tmp)
        return NULL;
    path = ft_split(tmp, '/');
    free(tmp);
    return path;
}
void init_cmd2(t_shell *shell, int i)
{
    shell->cmd[i].sts = 0;
    shell->cmd[i].redirin = -1;
    shell->cmd[i].redirout = -1;
    shell->cmd[i].cmd = exec_dir(shell, i);
    if (!shell->cmd[i].cmd)
        shell->cmd[i].cmd = 0;
    if(shell->cmd[i].cmd)
    {
        shell->cmd[i].path = shell->cmd[i].cmd[0];
        shell->cmd[i].builtin = check_cmd(shell->cmd[i].cmd[0]);
    }
}
void init_cmd(t_shell *shell, int proc)
{
    int i = 0;
    while (i < proc)
    {
        shell->cmd[i].index = i;
        shell->cmd[i].cmd = get_cmd(shell->ap[i]);  // Get the command arguments
        if (!shell->cmd[i].cmd)
        {
            printf("Memory allocation failed\n");
            exit(1);
        }
        shell->cmd[i].input_fd = 0;  // Set default input and output file descriptors
        shell->cmd[i].output_fd = 1;
        
        init_cmd2(shell, i);  // Initialize additional fields like path, builtin, etc.
        i++;
    }
}
