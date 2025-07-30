/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:44:58 by frey-gal          #+#    #+#             */
/*   Updated: 2025/07/30 11:45:30 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static bool	all_threads_running(t_feast *feast, pthread_mutex_t *mutex)
{
	bool	value;

	value = false;
	mutex_handler(feast, mutex, O_LOCK);
	if (feast->n_philos == feast->threads_running)
		value = true;
	mutex_handler(feast, mutex, O_UNLOCK);
	return (value);
}

static bool	check_vitals(t_feast *feast, t_plato *plato)
{
	long	elapsed;

	if (get_bool(feast, &plato->mutex, &plato->full))
		return (true);
	elapsed = get_time(feast, MILLISECOND) \
		- get_long(feast, &plato->mutex, &plato->t_lastmeal);
	if (elapsed > feast->tt_die / 1e3)
		return (false);
	return (true);
}

void	*monitor_feast(void *data)
{
	t_feast	*feast;
	int		i;

	feast = (t_feast *)data;
	while (all_threads_running(feast, &feast->data_mutex) == false)
		;
	while (get_bool(feast, &feast->data_mutex, &feast->finish) == false)
	{
		i = 0;
		while (i < feast->n_philos && get_bool(feast, &feast->data_mutex,
				&feast->finish) == false)
		{
			if (check_vitals(feast, &feast->philos[i]) == false)
			{
				change_plato_status(&feast->philos[i], DIE);
				set_bool(feast, &feast->write_mutex, &feast->finish, true);
			}
			i++;
		}
	}
	return (NULL);
}
