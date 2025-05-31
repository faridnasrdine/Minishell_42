/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:21:10 by nafarid           #+#    #+#             */
/*   Updated: 2025/05/11 13:21:10 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int g_last_exit_code = 0; // Global variable to store the last exit code
void exit_code(t_shell *shell, int proc)
{
    int i = 0;
    int status = 0;
    while (i < proc)
    {
        if (shell->pid[i] > 0) // check if the process ID is valid
        {
            waitpid(shell->pid[i], &status, 0); // wait for the child process to finish
            if (WIFEXITED(status)) // check if the child process exited normally
                g_last_exit_code = WEXITSTATUS(status); // get the exit status of the child process
        }
        i++;
    }
}
void run_child(t_shell *shell, int i, int status)
{
    shell->pid[status] = fork(); // create a new process
    if(shell->pid[status] < 0) // check if fork failed
    {
        printf("Fork failed\n"); // print error message
        return;
    }
    if(shell->pid[status] == 0)
    {
        child(shell, i); // run child process
    }

}

void fork_process(t_shell *shell, int proc)
{
    int i = 0;
    int status = 0;

    while (i < proc)
    {
        if (shell->cmd[i].cmd)
        {
            if (shell->cmd[i].cmd[0])  // If there's a command to execute
            {
                shell->child_run = 1;  // Mark that a child process is running
                run_child(shell, i, status);  // Fork the child process to run the command
                status++;
            }
        }
        i++;
    }
    exit_code(shell, proc);  // Wait for all child processes and collect exit codes
    shell->child_run = 0;  // Reset the child_run flag
}

