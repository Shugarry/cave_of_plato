/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:39:45 by frey-gal          #+#    #+#             */
/*   Updated: 2025/07/29 18:51:31 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static bool	pthread_error(int status)
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
	else if (status == EAGAIN)
		return (true);
	return (false);
}

void	mutex_handler(t_feast *feast, pthread_mutex_t *mutex, t_opt option)
{
	int	status;

	status = 0;
	if (option == O_LOCK)
		status = pthread_mutex_lock(mutex);
	else if (option == O_UNLOCK)
		status = pthread_mutex_unlock(mutex);
	else if (option == O_INIT)
		status = pthread_mutex_init(mutex, NULL);
	else if (option == O_DESTROY)
		status = pthread_mutex_destroy(mutex);
	if (pthread_error(status) == true)
		plato_exit(feast, "Mutex error", status);
}

void	thread_create(t_feast *feast, pthread_t *thread,
					void *(*func)(void *), void *data)
{
	int	status;

	status = 0;
	status = pthread_create(thread, NULL, func, data);
	if (pthread_error(status) == true)
		plato_exit(feast, "Thread error", status);
}

void	thread_handler(t_feast *feast, pthread_t *thread, t_opt option)
{
	int	status;

	status = 0;
	if (option == O_JOIN)
		status = pthread_join(*thread, NULL);
	else if (option == O_DETACH)
		status = pthread_detach(*thread);
	if (pthread_error(status) == true)
		plato_exit(feast, "Thread error", status);
}
