/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:21:07 by nafarid           #+#    #+#             */
/*   Updated: 2025/05/11 13:21:07 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Function to count the number of non-builtin commands
int nbr_of_pid(t_shell *shell, int proc)
{
    int i;
    int pid_count;

    i = 0;
    pid_count = 0;
    while (i < proc)
    {
        if (shell->cmd[i].cmd && shell->cmd[i].builtin == 0)  // Check if it's not a builtin command
            pid_count++;
        i++;
    }
    return pid_count;
}

// Create an array of PIDs to store the process IDs
int *create_pid(int pid_count)
{
    int *pids;

    pids = malloc(sizeof(int) * pid_count);
    if (!pids)
    {
        perror("Memory allocation failed");
        return NULL;
    }
    return pids;
}

// Execute the commands with support for pipes and forking processes
void execute_cmd(t_shell *shell)
{
    int proc = cnt_string(shell->ap);  // Assuming cnt_string counts the commands to execute
    int pipes = proc - 1;
  
    // Set up the shell structure
    shell->pipes = pipes;
    shell->fds = NULL;
    shell->pid = NULL;
    shell->cmd = calloc(proc, sizeof(t_command));  // Allocate memory for the commands
    if (!shell->cmd)
    {
        perror("Memory allocation failed");
        return;
    }

    // Initialize command structure
    init_cmd(shell, proc);

    // Create PID array if there are non-builtin commands
    if (nbr_of_pid(shell, proc) > 0)
        shell->pid = create_pid(nbr_of_pid(shell, proc));

    // Fork processes
    fork_process(shell, proc);

    // Free allocated memory after execution
    if (shell->cmd)
        free(shell->cmd);
    if (shell->pid)
        free(shell->pid);
}
