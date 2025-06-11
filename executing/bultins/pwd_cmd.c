/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:56:51 by nafarid           #+#    #+#             */
/*   Updated: 2025/06/11 15:20:11 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int pwd_cmd()
{
    char *path;

    path = getcwd(NULL, 0);
    if(!path)
    {
        free(path);
        return 1;
    }
    printf("%s\n", path);
    free(path);
    return 0;
}