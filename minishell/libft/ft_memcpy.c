/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:16:20 by aoussama          #+#    #+#             */
/*   Updated: 2024/11/07 14:50:45 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest_str, const void *src_str, size_t n)
{
	size_t				i;
	unsigned char		*d;
	unsigned const char	*s;

	if (src_str == NULL && dest_str == NULL)
		return (NULL);
	i = 0;
	d = (unsigned char *)dest_str;
	s = (unsigned char *)src_str;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
