#include "../minishell.h"



int signal_exec(t_data *data)
{
    int i = 0;
    int j = 0;
    int status = 0;
    t_list *cmd_list = data->cmd_list;
    t_cmd_exec *cmd_exec = NULL;

    while (cmd_list)
    {
        if (cmd_list->type == T_IDENTIFIER)
        {
            cmd_exec = create_cmd_exec(cmd_list);
            if (!cmd_exec)
                return (1);
            if (execve(cmd_exec->path, cmd_exec->argv, data->envp) == -1)
            {
                perror("execve");
                free_cmd_exec(cmd_exec);
                return (1);
            }
        }
        cmd_list = cmd_list->next;
    }
    return (0);
}