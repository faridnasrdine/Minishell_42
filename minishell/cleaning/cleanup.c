/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 23:41:59 by hounejja          #+#    #+#             */
/*   Updated: 2025/08/01 16:06:27 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup(t_cmd_exec **env_lst, t_cmd **cmd,
	t_cmd *exec_cmd, char **env)
{
    (void)cmd;
    (void)exec_cmd;
	if (env)
		arr_free(env);
	if (env_lst)
		lst_clear(env_lst, free);
	if (exec_cmd && exec_cmd != *cmd)
		cmd_free(&exec_cmd);
	if (cmd)
		cmd_free(cmd);
}


t_gc *create_node(void *data)
{
    t_gc *new_node = malloc(sizeof(t_gc));
    if (!new_node)
        return NULL;
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

t_gc *lastnode(t_gc *head)
{
    if (!head)
        return NULL;
    while (head->next)
        head = head->next;
    return head;
}

void add_back(t_gc **head, t_gc *node)
{
    if (!*head)
        *head = node;
    else
    {
        t_gc *tmp = lastnode(*head);
        tmp->next = node;
    }
}

void *ft_malloc(size_t size, t_gc **gc)
{
    void *ptr = malloc(size);
    if (!ptr)
        return NULL;
    t_gc *new_node = create_node(ptr);
    if (!new_node)
    {
        free(ptr);
        return NULL;
    }
    add_back(gc, new_node);
    return ptr;
}
