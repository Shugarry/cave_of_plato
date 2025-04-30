/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:12:00 by frey-gal          #+#    #+#             */
/*   Updated: 2025/04/30 17:12:39 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosphers.h"

void free_exit(t_dinnertable *dinnertable, int status, char  *msg)
{
	if (msg)
		printf("%s\n", msg);
	// TODO: free linked list
	exit(status);
}
