/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:21:16 by nafarid           #+#    #+#             */
/*   Updated: 2025/05/11 13:21:16 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_3(char *path, char *cmd, char c)
{
	char	*s;
	int		i;
	int		len;

	if (!path || !cmd)
		return (NULL);
	len = strlen(path) + strlen(cmd);
	s = malloc(len + 2);
	if (!s)
		return (NULL);
	i = 0;
	while (path[i])
	{
		s[i] = path[i];
		i++;
	}
	s[i++] = c;
	while (*cmd)
	{
		s[i] = *cmd++;
		i++;
	}
	s[i] = '\0';
	return (s);
}
char	*ft_getenv(char *var, t_list *shell)
{
	t_list	*temp;

	temp = shell->content;
	while (temp)
	{
		if (strcmp(var, temp->type) == 0)
			return (temp->content);
		temp = temp->next;
	}
	return (NULL);
}
int list_size(t_list *shell)
{
    int		i;
    t_list	*temp;

    i = 0;
    temp = shell->content;
    while (temp)
    {
        i++;
        temp = temp->next;
    }
    return (i);
}
int cnt_string(char **str)
{
    int i;

    i = 0;
    if(!str)
        return 0;
    while(str[i])
        i++; 
    return i;
}