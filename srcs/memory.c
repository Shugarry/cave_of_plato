/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:51:09 by frey-gal          #+#    #+#             */
/*   Updated: 2025/07/17 17:08:07 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosphers.h"

void	*memlist_alloc(t_dinnertable *dinnertable, size_t size)
{
	t_list	*node;
	void	*ptr;

	if (!dinnertable)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		plato_exit(dinnertable, "Memory allocation failure", EXIT_FAILURE);
	node = ft_lstnew(ptr);
	if (!node)
	{
		free(ptr);
		plato_exit(dinnertable, "Memory allocation failure", EXIT_FAILURE);
	}
	ft_lstadd_front(&dinnertable->memlist, node);
	return (ptr);
}

void	*memlist_add(t_dinnertable *dinnertable, void *ptr)
{
	t_list	*node;

	if (!dinnertable)
		return (NULL);
	if (!ptr)
		return (NULL);
	node = ft_lstnew(ptr);
	if (!node)
	{
		free(ptr);
		plato_exit(dinnertable, "Memory allocation failure", EXIT_FAILURE);
	}
	ft_lstadd_front(&dinnertable->memlist, node);
	return (ptr);
}

void	memlist_free_ptr(t_dinnertable *dinnertable, void *ptr)
{
	t_list	*current;
	t_list	*prev;

	if (!dinnertable || !ptr || !dinnertable->memlist)
		return ;
	if ((dinnertable->memlist)->content == ptr)
	{
		current = dinnertable->memlist;
		dinnertable->memlist = (dinnertable->memlist)->next;
		ft_lstdelone(current, free);
		return ;
	}
	prev = dinnertable->memlist;
	current = (dinnertable->memlist)->next;
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

