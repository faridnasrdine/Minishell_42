/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 09:56:09 by aoussama          #+#    #+#             */
/*   Updated: 2024/11/07 10:18:31 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*res;

	i = nmemb * size;
	res = (void *)malloc(i);
	if (res == NULL)
		return (NULL);
	ft_bzero(res, i);
	return (res);
}
