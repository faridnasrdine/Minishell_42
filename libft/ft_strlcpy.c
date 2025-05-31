/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:54:02 by aoussama          #+#    #+#             */
/*   Updated: 2024/11/04 20:22:21 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j])
		j++;
	if (n < 1)
		return (j);
	while ((i < n - 1) && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (j);
}
// int main()
// {
// 	char p[] = "salam";
// 	char o[6];
// 	//ft_strlcpy(o,p, 5);
// 	// printf("%ld\n", ft_strlcpy(o,p, 5));
// 	printf("%ld\n",ft_strlcpy(o,p,8));
// }