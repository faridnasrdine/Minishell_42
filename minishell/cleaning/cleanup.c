/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:00:16 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/09 21:32:29 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_gc	*create_node(void *data)
{
	t_gc	*new_node;

	new_node = malloc(sizeof(t_gc));
	if (!new_node)
		return (NULL);
	new_node->data = data;
	new_node->next = NULL;
	return (new_node);
}

t_gc	*get_garbage_collecter(void *ptr)
{
	static t_gc	*gc;
	t_gc		*new_gc;
	t_gc		*tmp;

	if (ptr)
	{
		new_gc = create_node(ptr);
		if (gc == NULL)
			gc = new_gc;
		else
		{
			tmp = gc;
			while (tmp->next)
			{
				tmp = tmp->next;
			}
			tmp->next = new_gc;
		}
	}
	return (gc);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("Minishell: Memory allocation failed!");
		free_grabage();
		exit(2);
	}
	get_garbage_collecter(ptr);
	return (ptr);
}

void	free_grabage(void)
{
	t_gc	*gc;
	t_gc	*tmp;

	gc = get_garbage_collecter(NULL);
	while (gc)
	{
		tmp = gc;
		gc = gc->next;
		free(tmp->data);
		tmp->data = NULL;
		free(tmp);
		tmp = NULL;
	}
}
