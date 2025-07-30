/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:38:29 by frey-gal          #+#    #+#             */
/*   Updated: 2025/07/29 18:36:06 by frey-gal         ###   ########.fr       */
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

void	change_plato_status(t_plato *plato, t_status status)
{
	t_feast	*feast;
	long	elapsed;
	
	feast = plato->feast;
	elapsed = get_time(feast, MILLISECOND) - feast->stopwatch;
	mutex_handler(feast, &feast->write_mutex, O_LOCK);
	if (TAKE_FORK_A == status && !get_bool(feast, &feast->data_mutex, &feast->dessert_time))
		printf("TIME: %-6ld | Philosopher %d has taken a fork [%d]\n", elapsed, plato->id, plato->fork_a->id);
	else if (TAKE_FORK_B == status && !get_bool(feast, &feast->data_mutex, &feast->dessert_time))
		printf("TIME: %-6ld | Philosopher %d has taken a fork [%d]\n", elapsed, plato->id, plato->fork_b->id);
	else if (EAT == status && !get_bool(feast, &feast->data_mutex, &feast->dessert_time))
		printf("TIME: %-6ld | Philosopher %d is eating\n", elapsed, plato->id);
	else if (SLEEP == status && !get_bool(feast, &feast->data_mutex, &feast->dessert_time))
		printf("TIME: %-6ld | Philosopher %d is sleeping\n", elapsed, plato->id);
	else if (THINK == status && !get_bool(feast, &feast->data_mutex, &feast->dessert_time))
		printf("TIME: %-6ld | Philosopher %d is thinking\n", elapsed, plato->id);
	else if (DIE == status && !get_bool(feast, &feast->data_mutex, &feast->dessert_time))
		printf("TIME: %-6ld | Philosopher %d has died\n", elapsed, plato->id);
	mutex_handler(feast, &feast->write_mutex, O_UNLOCK);
}
