/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:55:00 by aoussama          #+#    #+#             */
/*   Updated: 2025/05/01 17:40:55 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_pos(char *str,int *i)
{
    char c;
    if (str[*i] == '\'' || str[*i] == '"')
    {
        c = str[*i];
        (*i)++;
        while (str[*i] && str[*i] != c)
            (*i)++;
        if (str[*i] == c)
            (*i)++;
    }else{
        while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != ' ' && !is_meta(str[*i]))
            (*i)++;
    }
}
t_list *chr_meta(char *str,int *i)
{
    if (str[*i] == '<')
    {
        if (str[(*i) + 1] == '<')
        {
            if (is_meta(str[(*i) + 2]))
                return (write (1,"parse error\n",12),NULL);
            return ((*i) += 2,fill_node(ft_strdup("<<"),T_DLESS));
        }
        else
            return ((*i)++,fill_node(ft_strdup("<"),T_LESS));
    }else if (str[*i] == '>')
    {
        if (str[(*i) + 1] == '>')
        {
            if (is_meta(str[(*i) + 2]))
                return (write (1,"parse error\n",12),NULL);
            return ((*i) += 2,fill_node(ft_strdup(">>"),T_DGREAT));
        }
        else
            return ((*i)++,fill_node(ft_strdup(">"),T_GREAT));
    }else if (str[*i] == '|')
        return ((*i)++,fill_node(ft_strdup("|"),T_PIPE));
    return (NULL);
}
t_list *split_cmd(char *str)
{
    int i;
    int start;
    t_list *head = NULL;
    if (!str)
        return (NULL);
    i = 0;
    while (str[i] == ' ')
            i++;
    while (str[i])
    {
        while (str[i] == ' ')
            i++;
        start = i;
        while (str[i] && str[i] != ' ' && is_meta(str[i]) != 1)
            get_pos(str,&i);
        if (is_meta(str[i]))
        {
            if (ft_lstadd_back(&head,chr_meta(str,&i)) == 1)   
                 return (ft_lstclear(&head), NULL);
        }
        else
        {   
            if(ft_lstadd_back(&head,fill_node(ft_substr(str,start,i - start),T_IDENTIFIER)) == 1)
             return (ft_lstclear(&head), NULL); 
        }
    }
    return (head);
}

t_list *paring_cmd(char *cmd)
{
    t_list *args = split_cmd(cmd);
    t_list *tmp = args;

    if (!tmp)
    {
        write(1, "error\n", 6);
        return NULL;
    }
    if (checking_cmd(&args) == 1)
        return NULL;
    while (tmp)
    {
        tmp->content = checking_dolar(tmp->content);
        tmp->content = skip_qouts(tmp->content);
        tmp = tmp->next;
    }
    return args;
}

char **list_to_array(t_list *list)
{
    int i = 0;
    t_list *tmp = list;
    while (tmp)
    {
        if (tmp->type == T_IDENTIFIER)
            i++;
        tmp = tmp->next;
    }
    char **arr = malloc(sizeof(char *) * (i + 1));
    if (!arr)
        return (NULL);

    int j = 0;
    tmp = list;
    while (tmp)
    {
        if (tmp->type == T_IDENTIFIER)
        {
            arr[j] = ft_strdup(tmp->content);
            j++;
        }
        tmp = tmp->next;
    }
    arr[j] = NULL;
    return arr;
}


t_cmd_exec *create_cmd_exec(t_list *cmd_list)
{
    t_cmd_exec *cmd_exec = malloc(sizeof(t_cmd_exec));
    if (!cmd_exec)
        return (NULL);

    // Convert the list to an array of arguments
    cmd_exec->argv = list_to_array(cmd_list);
    cmd_exec->path = NULL;  // Path is not assigned yet
    cmd_exec->hd_fd = -1;  // Default value for file descriptor
    return cmd_exec;
}

