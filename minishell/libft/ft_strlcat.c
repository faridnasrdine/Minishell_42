/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:55:53 by aoussama          #+#    #+#             */
/*   Updated: 2024/11/07 15:01:11 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	lend;
	size_t	lens;
	size_t	i;

	lens = ft_strlen(src);
	if (size == 0 && !dest)
		return (lens);
	lend = ft_strlen(dest);
	i = 0;
	if (lend >= size)
		return (lens + size);
	while (lend + i < size - 1 && src[i] != '\0')
	{
		dest[lend + i] = src[i];
		i++;
	}
	dest[lend + i] = '\0';
	return (lend + lens);
}
