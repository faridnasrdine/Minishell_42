/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_meta.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:08:43 by aoussama          #+#    #+#             */
/*   Updated: 2025/05/01 17:11:05 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_meta(t_list **list)
{
    t_list *tmp;
    tmp = *list;

    while (tmp)
    {
        while (tmp->type == T_IDENTIFIER)
        {
            
        }
    }
}