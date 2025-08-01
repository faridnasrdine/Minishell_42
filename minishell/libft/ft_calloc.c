/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 09:56:09 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/01 09:27:59 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*res;

	i = nmemb * size;
	res = (void *)ft_malloc(i);
	if (res == NULL)
		return (NULL);
	ft_bzero(res, i);
	return (res);
}
