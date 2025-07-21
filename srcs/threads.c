/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:39:45 by frey-gal          #+#    #+#             */
/*   Updated: 2025/07/19 22:24:52 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosphers.h"

bool	mutex_error(int status)
{
	if (status == 0)
		return (false);
	else if (status == EAGAIN)
		return (true);
	else if (status == EINVAL)
		return (true);
	else if (status == EINVAL)
		return (true);
	else if (status == EINVAL)
		return (true);
	else if (status == EINVAL)
		return (true);
}

void	mutex_handler(t_dinnertable *dinnertable, pthread_mutex_t *mutex, t_mutex_opt option)
{
	int	status;

	status = 0;
	if (option == LOCK)
		status = pthread_mutex_lock(mutex);
	else if (option == UNLOCK)
		status = pthread_mutex_unlock(mutex);
	else if (option == INIT)
		status = pthread_mutex_init(mutex, NULL);
	else if (option == DESTROY)
		status = pthread_mutex_destroy(mutex);
	else
		;
	if (mutex_error(status) == true)
		plato_exit(dinnertable, "Mutex error", errno);
		
}
