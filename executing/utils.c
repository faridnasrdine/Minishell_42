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
void	ft_strncpy(char *dest, const char *src, int n)
{
	int	i;

	i = 0;
	while ((i < n) && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}
void	ft_strcat(char *dest, const char *src)
{
	int	lend;
	int	lens;
	int	i;

	lens = ft_strlen(src);
	if (!dest)
		return;
	lend = ft_strlen(dest);
	i = 0;
	while (src[i] != '\0')
	{
		dest[lend + i] = src[i];
		i++;
	}
	dest[lend + i] = '\0';
}
int	ft_strncmp(const char *str1, const char *str2, int n)
{
	int	i;

	i = 0;
	while (i < n && str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0')
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
