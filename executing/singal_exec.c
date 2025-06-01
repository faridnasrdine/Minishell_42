#include "../minishell.h"

int is_builtin(char *cmd)
{
    if (!cmd)
        return (0);
    if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || 
        !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export") ||
        !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") ||
        !ft_strcmp(cmd, "exit"))
        return (1);
    return (0);
}

char *find_command_path(char *cmd, char **envp)
{
    char *path_env;
    char **paths;
    char *full_path;
    char *temp;
    int i;

    (void)envp; // Suppress unused parameter warning

    if (!cmd || !*cmd)
        return (NULL);

    // If command contains '/', it's already a path
    if (ft_strchr(cmd, '/'))
    {
        if (access(cmd, F_OK | X_OK) == 0)
            return (ft_strdup(cmd));
        return (NULL);
    }

    // Get PATH environment variable
    path_env = getenv("PATH");
    if (!path_env)
        return (NULL);

    paths = ft_split(path_env, ':');
    if (!paths)
        return (NULL);

    i = 0;
    while (paths[i])
    {
        temp = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(temp, cmd);
        free(temp);

        if (access(full_path, F_OK | X_OK) == 0)
        {
            // Free paths array
            int j = 0;
            while (paths[j])
                free(paths[j++]);
            free(paths);
            return (full_path);
        }
        free(full_path);
        i++;
    }

    // Free paths array
    i = 0;
    while (paths[i])
        free(paths[i++]);
    free(paths);
    return (NULL);
}

int execute_single_command(t_data *data)
{
    t_cmd_exec *cmd_exec;
    int pid;
    int status;

    cmd_exec = create_cmd_exec(data->cmd_list);
    if (!cmd_exec || !cmd_exec->argv || !cmd_exec->argv[0])
        return (1);

    // Handle built-in commands
    if (is_builtin(cmd_exec->argv[0]))
    {
        data->exit_status = execute_builtin(cmd_exec);
        free_cmd_exec(cmd_exec);
        return (data->exit_status);
    }

    // Find command path
    cmd_exec->path = find_command_path(cmd_exec->argv[0], data->envp);
    if (!cmd_exec->path)
    {
        printf("minishell: %s: command not found\n", cmd_exec->argv[0]);
        free_cmd_exec(cmd_exec);
        data->exit_status = 127;
        return (127);
    }

    // Fork and execute
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free_cmd_exec(cmd_exec);
        return (1);
    }
    else if (pid == 0)
    {
        // Child process
        if (execve(cmd_exec->path, cmd_exec->argv, data->envp) == -1)
        {
            perror("execve");
            free_cmd_exec(cmd_exec);
            exit(126);
        }
    }
    else
    {
        // Parent process
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            data->exit_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            data->exit_status = 128 + WTERMSIG(status);
    }

    free_cmd_exec(cmd_exec);
    return (data->exit_status);
}

int execute_command(t_data *data){
    if (!data || !data->cmd_list)
        return (1);

    // For now, handle single commands only
    // TODO: Add pipe handling, redirections, etc.
    return (execute_single_command(data));
}

void free_cmd_exec(t_cmd_exec *cmd_exec)
{
    int i;

    if (!cmd_exec)
        return;

    if (cmd_exec->argv)
    {
        i = 0;
        while (cmd_exec->argv[i])
        {
            free(cmd_exec->argv[i]);
            i++;
        }
        free(cmd_exec->argv);
    }

    if (cmd_exec->path)
        free(cmd_exec->path);

    if (cmd_exec->hd_fd > 0)
        close(cmd_exec->hd_fd);

    free(cmd_exec);
}