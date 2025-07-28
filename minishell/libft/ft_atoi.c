/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:04:22 by aoussama          #+#    #+#             */
/*   Updated: 2025/05/30 18:48:29 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_and_return(const char *str, int *k)
{
	char	*new_str;

	new_str = (char *)str;
	*k = 1;
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("Minishell: exit: ", 2);
	ft_putstr_fd(new_str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (255);
}

static int	check_overf(const char *str, int i, int *k)
{
	int		sign;
	char	max_long[20];

	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (ft_strlen(&(str[i])) > 19)
		return (print_and_return(str, k));
	else if (ft_strlen(&str[i]) == 19)
	{
		if (sign == 1)
			ft_strlcpy(max_long, "9223372036854775807", 20);
		else
			ft_strlcpy(max_long, "9223372036854775808", 20);
		if (ft_strncmp(&(str[i]), max_long, 20) > 0)
			return (print_and_return(str, k));
	}
	return (0);
}

long	ft_atoi(const char *str, int *k)
{
	int		i;
	int		sin;
	long	result;

	i = 0;
	sin = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (check_overf(str, i, k) == 255)
		return (255);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sin = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sin);
}
