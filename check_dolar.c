/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dolar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:37:05 by aoussama          #+#    #+#             */
/*   Updated: 2025/04/30 18:20:50 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strjoin_free(char *s1, char *s2)
{
    char *joined;
    
    joined = ft_strjoin(s1, s2);
    free(s1);
    free(s2);
    return joined;
}
static void init_solar(t_dolar *dolar)
{
    dolar->i = 0;
    dolar->start = 0;
    dolar->result = ft_strdup("");
    dolar->tmp = NULL;
    dolar->var_name = NULL;
    dolar->var_value = NULL;
    dolar->in_single_quote = 0;
    dolar->in_double_quote = 0;
}
char *checking_dolar(char *str)
{
    t_dolar dolar;

    init_solar(&dolar);
    while (str[dolar.i])
    {
        if (str[dolar.i] == '\'' && !dolar.in_double_quote)
        {
            dolar.in_single_quote = !dolar.in_single_quote;
            dolar.tmp = ft_substr(str, dolar.i, 1);
            dolar.result = ft_strjoin_free(dolar.result, dolar.tmp);
            dolar.i++;
        }
        else if (str[dolar.i] == '"' && !dolar.in_single_quote)
        {
            dolar.in_double_quote = !dolar.in_double_quote;
            dolar.tmp = ft_substr(str, dolar.i, 1);
            dolar.result = ft_strjoin_free(dolar.result, dolar.tmp);
            dolar.i++;
        }
        else if (str[dolar.i] == '$' && !dolar.in_single_quote)
        {
            dolar.start = ++dolar.i;
            if(!ft_isalnum(str[dolar.i]))
                return (str);
            while (str[dolar.i] && (ft_isalnum(str[dolar.i]) || str[dolar.i] == '_'))
                dolar.i++;
            dolar.var_name = ft_substr(str, dolar.start, dolar.i - dolar.start);
            dolar.var_value = getenv(dolar.var_name);
            free(dolar.var_name);
            if (dolar.var_value)
                dolar.result = ft_strjoin_free(dolar.result, ft_strdup(dolar.var_value));
        }
        else
        {
            dolar.tmp = ft_substr(str, dolar.i, 1);
            dolar.result = ft_strjoin_free(dolar.result, dolar.tmp);
            dolar.i++;
        }
    }
    return (dolar.result);
}
