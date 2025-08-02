/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:59:56 by aoussama          #+#    #+#             */
/*   Updated: 2024/11/07 16:29:22 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*res;
	size_t			s_len;
	size_t			lend;

	if (!s)
		return (NULL);
	i = 0;
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	if (len < s_len - start)
		lend = len;
	else
		lend = s_len - start;
	res = (char *)malloc((lend + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (i < lend)
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}
