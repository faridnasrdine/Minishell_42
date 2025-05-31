/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:45:11 by aoussama          #+#    #+#             */
/*   Updated: 2024/11/05 17:36:50 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*reslt;
	int		len;
	long	j;

	j = n;
	len = ft_count(j);
	reslt = (char *)malloc((len + 1) * sizeof(char));
	if (!reslt)
		return (NULL);
	reslt[len] = '\0';
	len--;
	if (j == 0)
		reslt[len] = '0';
	if (j < 0)
	{
		reslt[0] = '-';
		j *= -1;
	}
	while (j > 0)
	{
		reslt[len] = (j % 10) + 48;
		j = j / 10;
		len--;
	}
	return (reslt);
}
