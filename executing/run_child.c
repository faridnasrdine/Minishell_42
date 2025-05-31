/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:21:13 by nafarid           #+#    #+#             */
/*   Updated: 2025/05/11 13:21:13 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_path(t_shell *shell, int i)
{
    char **path;
    char *home;
    int index;
    char *tmp;

    index = 0;
    if (!shell->cmd[0].cmd[0])
        return (NULL);
    home = ft_getenv("PATH", shell);  // Get the PATH environment variable
    if (!home)
        return (NULL);
    path = ft_split(home, ':');  // Split PATH into directories
    if (!path)
        return (NULL);

    while (path[index])  // Search for the command in each directory
    {
        tmp = ft_strjoin_3(path[index], shell->cmd[i].cmd[0], '/');
        if (access(tmp, X_OK) == 0)  // Check if command is executable
        {
            free(home);
            free(path);
            return (tmp);
        }
        free(tmp);
        index++;
    }
    free(home);
    free(path);
    return (NULL);  // Return NULL if command is not found
}

void check_redir(t_shell *shell, int i)
{
    DIR  *dir;

    dir = opendir(shell->cmd[i].path);
    if(dir && strncmp("./", shell->cmd->path, 2) == 0)
    {
        printf("minishell: %s: is a directory\n", shell->cmd[i].path);
        closedir(dir);
        exit(126);
    }
    if(dir)
    {
        closedir(dir);
        printf("minishell: %s: is a directory\n", shell->cmd[i].cmd[0]);
        exit(126);
    }
}
char **new_envp(t_shell *shell)
{
    char **envp;
    t_lexer_token *token;
    int j = 0;

    // Allocate memory for the new environment variable array
    envp = malloc(sizeof(char *) * (list_size(shell) + 1));
    if (!envp)
        return NULL;

    token = shell->tokens;

    while (shell->tokens)
    {
        if (shell->tokens->content)
        {
            // Allocate and create the environment variable string
            envp[j] = ft_strjoin_3(shell->tokens->var, shell->tokens->content, '=');
            j++;
        }
        shell->tokens = shell->tokens->next;
    }

    // Reset the tokens pointer to the original value
    shell->tokens = token;
    
    // NULL-terminate the envp array
    envp[j] = NULL;

    return envp;
}


void child(t_shell *shell, int i)
{
    char **envp;
    
    signal(SIGINT, SIG_DFL); // Reset signal handlers for child process
    signal(SIGQUIT, SIG_DFL);

    check_redir(shell, i);  // Check for redirection before execution
    
    // Try to find the path for the command
    if (shell->cmd[i].path && access(shell->cmd[i].path, X_OK) != 0)
    {
        shell->cmd[i].path = get_path(shell, i);  // Get the correct path
    }

    if (!shell->cmd[i].path)
    {
        if (!shell->cmd[i].cmd[0][0])
            printf("minishell: %s: command not found\n", shell->cmd[i].cmd[0]);
        else
            printf("minishell: %s: No such file or directory\n", shell->cmd[i].cmd[0]);
        exit(127);  // Exit with command not found error
    }

    envp = new_envp(shell);  // Create environment variables array
    dup2(shell->cmd[i].input_fd, STDIN_FILENO);  // Redirect input
    dup2(shell->cmd[i].output_fd, STDOUT_FILENO);  // Redirect output

    if (execve(shell->cmd[i].path, shell->cmd[i].cmd, envp) == -1)
    {
        perror("execve failed");  // Print any error with execve
        exit(1);
    }
}

