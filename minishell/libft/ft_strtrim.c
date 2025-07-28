/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houssam <houssam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:59:50 by aoussama          #+#    #+#             */
/*   Updated: 2025/07/06 01:21:30 by houssam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	first;
	size_t	last;
	size_t	i;
	char	*trim;

	if (!s1)
		return (NULL);
	first = 0;
	while (s1[first] && ft_strchr(set, s1[first]))
		first++;
	last = ft_strlen(s1);
	while (last > first && ft_strchr(set, s1[last]))
		last--;
	if (first <= last)
		trim = malloc(sizeof(char) * (last - first + 2));
	else
		trim = malloc(sizeof(char));
	if (!trim)
		return (NULL);
	i = 0;
	while (first <= last)
		trim[i++] = s1[first++];
	trim[i] = '\0';
	return (trim);
}
