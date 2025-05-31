/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:59:50 by aoussama          #+#    #+#             */
/*   Updated: 2024/11/07 15:04:58 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char c, const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	first;
	size_t	last;

	if (s1 == NULL)
		return (NULL);
	first = 0;
	last = ft_strlen(s1);
	if (first == last)
		return (ft_strdup(""));
	while (check(s1[first], set) == 1)
		first++;
	last--;
	while (check(s1[last], set) == 1)
		last--;
	return (ft_substr(s1, first, (last - first + 1)));
}
// int main()
// {
// 	char o[] = "salam jhjhvsa";
// 	char *r = ft_strtrim(o ,"sa");
// 	printf("%s\n",r);
// }