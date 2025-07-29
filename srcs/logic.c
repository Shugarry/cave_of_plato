/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 07:15:07 by frey-gal          #+#    #+#             */
/*   Updated: 2025/07/29 19:32:47 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

long	get_time(t_feast *feast, t_timecode timecode)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		plato_exit(feast, "gettimeofday() error: ", errno);
	if (timecode == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (timecode == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (timecode == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	return (-1);
}

void	threads_spinlock(t_feast *feast)
{
	while (get_bool(feast, &feast->access_mutex, &feast->philosophers_ready) == false)
		;
}

void	ft_usleep(t_feast *feast, long usec)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time(feast, MICROSECOND);
	while (get_time(feast, MICROSECOND) - start < usec)
	{
		if(get_bool(feast, &feast->access_mutex, &feast->dessert_time) == true)
			break ;
		elapsed = get_time(feast, MICROSECOND) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
		{
			while (get_time(feast, MICROSECOND) - start < usec)
				;
		}
	}
}

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
	if (feast->n_meals > 0 && plato->n_meals == feast->n_meals)
		set_bool(feast, &plato->mutex, &plato->full, true);
	mutex_handler(feast, &plato->fork_a->fork, O_UNLOCK);
	mutex_handler(feast, &plato->fork_b->fork, O_UNLOCK);
}

void	*feast_logic(void *data)
{
	t_plato *plato;
	t_feast	*feast;

	plato = (t_plato *)data;
	feast = plato->feast;
	threads_spinlock(feast);
	while (get_bool(feast, &feast->access_mutex, &feast->dessert_time) == false)
	{
		if (plato->full == true)	
			break ;
		plato_eat(plato);
		change_plato_status(plato, SLEEP);
		ft_usleep(feast, feast->tt_sleep);
		change_plato_status(plato, THINK);
	}
	return (NULL);
}

void	start_feast(t_feast *feast)
{
	int	i;

	i = 0;
	if (feast->n_meals == 0)
	{
		return ;
	}
	else if (feast->n_meals == 1)
	{
		; // TODO
	}
	else if (feast->n_meals == -1)
	{
		while (i < feast->n_philos)
		{
			thread_handler(feast, &feast->philos->thread_id, feast_logic, &feast->philos[i], O_CREATE);
			i++;
		}
	}

	feast->stopwatch = get_time(feast, MILLISECOND);
	set_bool(feast, &feast->access_mutex, &feast->philosophers_ready, true);

	i = 0;
	while (i < feast->n_philos)
	{
		thread_handler(feast, &feast->philos->thread_id, NULL, NULL, O_JOIN);
		i++;
	}

}
