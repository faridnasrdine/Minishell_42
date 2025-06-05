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


char *find_env(char **envp, char *name)
{
	char **env;
	char *pos;
	int len;
	int i = 0;
	if(!envp || !name)
		return NULL;
	len = ft_strlen(name);
	env = envp;
	while(env[i])
	{
		pos = ft_strchr(env[i], '=');
		if(pos && (pos - env[i]) == len && strncmp(env[i],name, len) == 0)
			return pos + 1;
		i++;
	}
	return NULL;
}
char **cop_env(char **env)
{
	int count;
	char **new_env;
	int i = 0;

	if(!env)
		return NULL;
	count = cnt_string(env);
	new_env = malloc(sizeof(char *) * count + 1);
	if(!new_env)
		return NULL;
	while(i < count)
	{
		new_env[i] = ft_strdup(env[i]);
		if(!new_env[i])
		{
			while(--i >= 0)
				free(new_env);
			free(new_env);
			return NULL;
		}
		i++;
	}
	new_env[count] = NULL;
	return new_env;
}
char	*ft_getenv(char **envp, char *var)
{
	return find_env(envp, var);
}
// int list_size(t_list *shell)
// {
//     int		i;
//     t_list	*temp;

//     i = 0;
//     temp = shell->content;
//     while (temp)
//     {
//         i++;
//         temp = temp->next;
//     }
//     return (i);
// }
// int cnt_string(char **str)
// {
//     int i;

//     i = 0;
//     if(!str)
//         return 0;
//     while(str[i])
//         i++; 
//     return i;
// }