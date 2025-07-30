/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 07:15:07 by frey-gal          #+#    #+#             */
/*   Updated: 2025/07/30 10:23:38 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	plato_eat(t_plato *plato)
{
	t_feast	*feast;
	
	feast = plato->feast;
	mutex_handler(feast, &plato->fork_a->fork, O_LOCK);
	change_plato_status(plato, TAKE_FORK_A);
	mutex_handler(feast, &plato->fork_b->fork, O_LOCK);
	change_plato_status(plato, TAKE_FORK_B);
	set_long(feast, &plato->mutex, &plato->time_lastmeal, get_time(feast, MILLISECOND));
	plato->n_meals++;
	change_plato_status(plato, EAT);
	ft_usleep(feast, feast->tt_eat);
	if (feast->max_meals > 0 && plato->n_meals == feast->max_meals)
		set_bool(feast, &plato->mutex, &plato->full, true);
	mutex_handler(feast, &plato->fork_a->fork, O_UNLOCK);
	mutex_handler(feast, &plato->fork_b->fork, O_UNLOCK);
}

void	thinking(t_plato *plato, bool output_status_flag)
{
	t_feast	*feast;
	long	tt_think;

	feast = plato->feast;
	if (output_status_flag == true)
		change_plato_status(plato, THINK);
	if (feast->n_philos % 2 == 0)
		return ;
	tt_think = feast->tt_eat * 2 - feast->tt_sleep;
	if (tt_think < 0)
		tt_think = 0;
	ft_usleep(feast, tt_think * 0.4);
}

void	desynchronize(t_plato *plato)
{
	if (plato->feast->n_philos % 2 == 0)
	{
		if (plato->id % 2 == 0)
			ft_usleep(plato->feast, 30000);
	}
	else
	{
		if (plato->id % 2 == 0)
			thinking(plato, false);
	}
}

bool	all_threads_running(t_feast *feast, pthread_mutex_t *mutex)
{
	bool	value;
	
	value = false;
	mutex_handler(feast, mutex, O_LOCK);
	if (feast->n_philos == feast->threads_running)
		value = true;
	mutex_handler(feast, mutex, O_UNLOCK);
	return (value);
}

void	*feast_logic(void *data)
{
	t_plato *plato;
	t_feast	*feast;

	plato = (t_plato *)data;
	feast = plato->feast;
	thread_creation_spinlock(feast);
	increase_long(feast, &feast->data_mutex, &feast->threads_running);
    set_long(feast, &plato->mutex, &plato->time_lastmeal, get_time(feast, MILLISECOND));
	desynchronize(plato);
	while (get_bool(feast, &feast->data_mutex, &feast->finish) == false)
	{
		plato_eat(plato);
		change_plato_status(plato, SLEEP);
		ft_usleep(feast, feast->tt_sleep);
		thinking(plato, true);
		if (plato->full == true)	
			break ;
	}
	return (NULL);
}

bool	check_vitals(t_feast *feast, t_plato *plato)
{
	long	elapsed;

	if (get_bool(feast, &plato->mutex, &plato->full))
		return (true);
	elapsed = get_time(feast, MILLISECOND) - get_long(feast, &plato->mutex, &plato->time_lastmeal);
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
		while (i < feast->n_philos && get_bool(feast, &feast->data_mutex, &feast->finish) == false)
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

void	*single_plato(void *data)
{
	t_plato *plato;
	t_feast	*feast;

	plato = (t_plato *)data;
	feast = plato->feast;
	thread_creation_spinlock(feast);
	change_plato_status(plato, TAKE_FORK_A);
	while (get_bool(feast, &feast->data_mutex, &feast->finish) == false)
		usleep(200);
	return (NULL);
}

void	start_feast(t_feast *feast)
{
	int	i;

	i = 0;
	if (feast->max_meals == 0)
		return ;
	else if (feast->n_philos == 1)
		thread_handler(feast, &feast->philos[0].thread_id, single_plato, &feast->philos[i], O_CREATE);
	else
	{
		while (i < feast->n_philos)
		{
			thread_handler(feast, &feast->philos[i].thread_id, feast_logic, &feast->philos[i], O_CREATE);
			i++;
		}
	}
	thread_handler(feast, &feast->monitor, monitor_feast, feast, O_CREATE);
	feast->stopwatch = get_time(feast, MILLISECOND);
	set_bool(feast, &feast->write_mutex, &feast->philosophers_ready, true);
	i = 0;
	while (i < feast->n_philos)
		thread_handler(feast, &feast->philos[i++].thread_id, NULL, NULL, O_JOIN);
	set_bool(feast, &feast->write_mutex, &feast->finish, true);
	thread_handler(feast, &feast->monitor, NULL, NULL, O_JOIN);
}
