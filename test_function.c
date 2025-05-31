/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:31:53 by aoussama          #+#    #+#             */
/*   Updated: 2025/05/01 17:05:09 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char *token_type_to_string(t_token_type type)
{
    if (type == T_IDENTIFIER)
        return "T_IDENTIFIER";
    if (type == T_PIPE)
        return "T_PIPE";
    if (type == T_AND)
        return "T_AND";
    if (type == T_OR)
        return "T_OR";
    // if (type == T_O_PARENT)
    //     return "T_O_PARENT";
    // if (type == T_C_PARENT)
        // return "T_C_PARENT";
    if (type == T_DGREAT)
        return "T_DGREAT";
    if (type == T_GREAT)
        return "T_GREAT";
    if (type == T_DLESS)
        return "T_DLESS";
    if (type == T_LESS)
        return "T_LESS";
    return "UNKNOWN";
}