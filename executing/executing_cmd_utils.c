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

void clear_data(t_data *data)
{
    if(!data->cmd_exec)
        return;
    if(data->cmd_exec)
        free_string(data->cmd_exec->argv);
    if(data->cmd_exec->path)
        free(data->cmd_exec->path);
}

void free_string(char **str)
{
    int i = 0;
    while(str[i])
    {
        free(str[i]);
        i++;
    }
    free(str[i]);
}