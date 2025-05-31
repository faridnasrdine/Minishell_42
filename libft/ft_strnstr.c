/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:51:30 by aoussama          #+#    #+#             */
/*   Updated: 2024/11/07 15:03:09 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	e;

	if (len == 0)
		return ((char *)big);
	i = 0;
	e = ft_strlen(little);
	if (little[i] == '\0')
		return ((char *)(big));
	while (big[i] != '\0' && len > i)
	{
		j = 0;
		while (i + j < len && big[i + j] == little[j] && little[j] != '\0')
		{
			j++;
		}
		if (e == j)
		{
			return ((char *)(big + i));
		}
		i++;
	}
	return (0);
}
