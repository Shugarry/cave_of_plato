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

bool	thread_error(int status)
{
	if (status == -1)
		return (true);
	else if (status == EINVAL)
		return (true);
	else if (status == EDEADLK)
		return (true);
	else if (status == EPERM)
		return (true);
	else if (status == ESRCH)
		return (true);
	else if (status == ENOMEM)
		return (true);
	else if (status == EBUSY)
		return (true);
	return (false);
}

void	mutex_handler(t_dinnertable *dinnertable, pthread_mutex_t *mutex, t_opt option)
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
	if (thread_error(status) == true)
		plato_exit(dinnertable, "Mutex error", status);
		
}

void	thread_handler(t_dinnertable *dinnertable, void *(*func)(void *),
					void *data, pthread_t *thread, t_opt option)
{
	int	status;

	status = 0;
	if (option == CREATE)
		status = pthread_create(thread, NULL, func, data);
	else if (option == JOIN)
		status = pthread_join(*thread, NULL);
	else if (option == DETACH)
		status = pthread_detach(*thread);
	else
		;
	if (thread_error(status) == true)
		plato_exit(dinnertable, "Thread error", status);
		
}
