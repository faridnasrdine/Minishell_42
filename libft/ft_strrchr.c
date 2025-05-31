/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:33:05 by aoussama          #+#    #+#             */
/*   Updated: 2024/11/04 10:02:12 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
// int main()
// {
// 	char h[] = "soplamm ohhphh";
// 	char *l = ft_strrchr(h,'p');
// 	if(l)
// 	{
// 		printf("%s\n", l);
// 	}else
// 		printf("mkynch");
// }
