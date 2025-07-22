/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 07:15:07 by frey-gal          #+#    #+#             */
/*   Updated: 2025/07/22 09:59:37 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosphers.h"
#include <sys/time.h>

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
	while (get_bool(feast, &feast->mutex, &feast->philosophers_ready))
		;
}

void	ft_usleep(long usec, t_feast *feast)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time(feast, MICROSECOND);
	while (get_time(feast, MICROSECOND) - start < usec)
	{
		if(get_bool(feast, &feast->mutex, &feast->dessert_time) == true)
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

void	*feast_logic(void *data)
{
	t_plato *plato;
	t_feast	*feast;

	plato = (t_plato *)data;
	feast = plato->feast;
	threads_spinlock(feast);
	while (get_bool(feast, &feast->mutex, &feast->dessert_time) == false)
	{
		if (plato->fed == true)	
			break ;

		// eat(plato);

		// write_plato_status
		// ft_usleep();
		
		// thinking
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
		}
	}

	feast->stopwatch = get_time(feast, MILLISECOND);
	set_bool(feast, &feast->mutex, &feast->philosophers_ready, true);

	i = 0;
	while (i < feast->n_philos)
	{
		thread_handler(feast, &feast->philos->thread_id, NULL, NULL, O_JOIN);
		i++;
	}

}
