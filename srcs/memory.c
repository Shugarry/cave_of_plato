/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:51:09 by frey-gal          #+#    #+#             */
/*   Updated: 2025/07/29 18:36:47 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*memlist_alloc(t_feast *feast, size_t size)
{
	t_list	*node;
	void	*ptr;

	if (!feast)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		plato_exit(feast, "Memory allocation failure", EXIT_FAILURE);
	node = ft_lstnew(ptr);
	if (!node)
	{
		free(ptr);
		plato_exit(feast, "Memory allocation failure", EXIT_FAILURE);
	}
	ft_lstadd_front(&feast->memlist, node);
	return (ptr);
}

void	*memlist_add(t_feast *feast, void *ptr)
{
	t_list	*node;

	if (!feast)
		return (NULL);
	if (!ptr)
		return (NULL);
	node = ft_lstnew(ptr);
	if (!node)
	{
		free(ptr);
		plato_exit(feast, "Memory allocation failure", EXIT_FAILURE);
	}
	ft_lstadd_front(&feast->memlist, node);
	return (ptr);
}

void	memlist_free_ptr(t_feast *feast, void *ptr)
{
	t_list	*current;
	t_list	*prev;

	if (!feast || !ptr || !feast->memlist)
		return ;
	if ((feast->memlist)->content == ptr)
	{
		current = feast->memlist;
		feast->memlist = (feast->memlist)->next;
		ft_lstdelone(current, free);
		return ;
	}
	prev = feast->memlist;
	current = (feast->memlist)->next;
	while (current)
	{
		if (current->content == ptr)
		{
			prev->next = current->next;
			ft_lstdelone(current, free);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
