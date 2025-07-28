/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:13:24 by aoussama          #+#    #+#             */
/*   Updated: 2024/11/13 22:51:03 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(const char *s, char c)
{
	int	i;
	int	count;
	int	word;

	i = 0;
	count = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			count = 0;
		}
		else if (count == 0)
		{
			word++;
			count = 1;
		}
		i++;
	}
	return (word);
}

static char	*str_d(const char *s, int start, int finish)
{
	char	*result;
	int		i;

	result = (char *)malloc((finish - start + 1) * sizeof(char));
	if (result == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (start < finish)
	{
		result[i] = s[start];
		i++;
		start++;
	}
	result[i] = '\0';
	return (result);
}

static void	*ft_free(char **result)
{
	int	i;

	i = 0;
	while (result[i] != NULL)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		j;
	int		start;

	if (s == NULL)
		return (NULL);
	result = (char **)malloc((count_word(s, c) + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (start < i)
			result[j++] = str_d(s, start, i);
		if (result[j - 1] == NULL)
			return (ft_free(result));
	}
	return (result[j] = NULL, result);
}
// int main()
// {
// 	char p[] = ",h";
// 	char **o = ft_split(p,',');
// 	int i = 0;
// 	if (o == NULL){
// 		printf("bbbb\n");
// 		return (0);
// 	}
// 	while (o[i])
// 	{
// 		printf("%s$\n",o[i]);
// 		i++;
// 	}
// }