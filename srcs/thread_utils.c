/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 07:25:03 by frey-gal          #+#    #+#             */
/*   Updated: 2025/07/30 07:27:05 by frey-gal         ###   ########.fr       */
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

void	ft_usleep(t_feast *feast, long usec)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time(feast, MICROSECOND);
	while (get_time(feast, MICROSECOND) - start < usec)
	{
		if(get_bool(feast, &feast->data_mutex, &feast->finish) == true)
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

void	thread_creation_spinlock(t_feast *feast)
{
	while (get_bool(feast, &feast->data_mutex, &feast->philosophers_ready) == false)
		;
}

void	change_plato_status(t_plato *plato, t_status status)
{
	t_feast	*feast;
	long	elapsed;
	
	feast = plato->feast;
	elapsed = get_time(feast, MILLISECOND) - feast->stopwatch;
	mutex_handler(feast, &feast->write_mutex, O_LOCK);
	if (TAKE_FORK_A == status && !get_bool(feast, &feast->data_mutex, &feast->finish))
		printf("TIME: %-6ld | Philosopher %d has taken a fork [%d]\n", elapsed, plato->id, plato->fork_a->id);
	else if (TAKE_FORK_B == status && !get_bool(feast, &feast->data_mutex, &feast->finish))
		printf("TIME: %-6ld | Philosopher %d has taken a fork [%d]\n", elapsed, plato->id, plato->fork_b->id);
	else if (EAT == status && !get_bool(feast, &feast->data_mutex, &feast->finish))
		printf("TIME: %-6ld | Philosopher %d is eating\n", elapsed, plato->id);
	else if (SLEEP == status && !get_bool(feast, &feast->data_mutex, &feast->finish))
		printf("TIME: %-6ld | Philosopher %d is sleeping\n", elapsed, plato->id);
	else if (THINK == status && !get_bool(feast, &feast->data_mutex, &feast->finish))
		printf("TIME: %-6ld | Philosopher %d is thinking\n", elapsed, plato->id);
	else if (DIE == status && !get_bool(feast, &feast->data_mutex, &feast->finish))
		printf("TIME: %-6ld | Philosopher %d has died\n", elapsed, plato->id);
	mutex_handler(feast, &feast->write_mutex, O_UNLOCK);
}
