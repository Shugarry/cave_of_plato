/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:38:29 by frey-gal          #+#    #+#             */
/*   Updated: 2025/07/30 07:26:30 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

bool	get_bool(t_feast *feast, pthread_mutex_t *mutex, bool *var)
{
	bool	value;

	mutex_handler(feast, mutex, O_LOCK);
	value = *var;
	mutex_handler(feast, mutex, O_UNLOCK);
	return (value);
}

void	set_bool(t_feast *feast, pthread_mutex_t *mutex, bool *var, bool set_to)
{
	mutex_handler(feast, mutex, O_LOCK);
	*var = set_to;
	mutex_handler(feast, mutex, O_UNLOCK);
}

long	get_long(t_feast *feast, pthread_mutex_t *mutex, long *var)
{
	long	value;

	mutex_handler(feast, mutex, O_LOCK);
	value = *var;
	mutex_handler(feast, mutex, O_UNLOCK);
	return (value);
}

void	set_long(t_feast *feast, pthread_mutex_t *mutex, long *var, long set_to)
{
	mutex_handler(feast, mutex, O_LOCK);
	*var = set_to;
	mutex_handler(feast, mutex, O_UNLOCK);
}

void	increase_long(t_feast *feast, pthread_mutex_t *mutex, long *var)
{
	mutex_handler(feast, mutex, O_LOCK);
	(*var)++;
	mutex_handler(feast, mutex, O_UNLOCK);
}
