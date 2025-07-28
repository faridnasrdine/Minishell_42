/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:39:02 by aoussama          #+#    #+#             */
/*   Updated: 2024/11/04 20:27:07 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*te1;
	unsigned char	*te2;

	i = 0;
	te1 = (unsigned char *)s1;
	te2 = (unsigned char *)s2;
	while (i < n)
	{
		if (te1[i] != te2[i])
			return (te1[i] - te2[i]);
		i++;
	}
	return (0);
}
