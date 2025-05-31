/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheking_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:21:00 by aoussama          #+#    #+#             */
/*   Updated: 2025/05/01 17:00:20 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_meta(char str)
{
    if (str == '<' || str == '>' || str == '|')
        return (1);
    else 
        return (0);
}

int finde_meta(t_list *list)
{
    while (list)
    {
        if (list->type != T_IDENTIFIER)
            return (1);
        list = list->next;
    }
    return (0);
}