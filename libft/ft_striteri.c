/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:20:55 by aoussama          #+#    #+#             */
/*   Updated: 2024/11/07 15:09:17 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f(i, s + i);
		i++;
	}
}

// void ft_up(unsigned int i,char *c)
// {
// 	if (i % 2 == 0)
// 	{
// 		c[i] -= 32;
// 	}

// }
// int main()
// {
// 	char p[] = "oussama";
// 	ft_striteri(p,ft_up);
// 	printf("%s\n",p);
// }