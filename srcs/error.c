/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:57:36 by frey-gal          #+#    #+#             */
/*   Updated: 2025/07/29 18:35:56 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	plato_exit(t_feast *feast, char *error_str, int error_num)
{
	ft_lstclear(&feast->memlist, free);
	if (error_num && error_str)
		perror(error_str);
	exit(error_num);
}

void	input_error(char *message)
{
	printf("Invalid args, format: ./philosphers a b c d e\n");
	printf("a: number of philosophers\n");
	printf("b: time to die\n");
	printf("c: time to eat\n");
	printf("d: time to sleep\n");
	printf("e: number of times philosophers must eat (optional)\n");
	if (message)
		printf("Error: %s\n", message);
	exit(EXIT_FAILURE);
}

void	debug_vars(t_feast *feast)
{
	printf("a: %ld philosophers\n", feast->n_philos);
	printf("b: %ld in microsecs\n", feast->tt_die);
	printf("c: %ld in microsecs\n", feast->tt_eat);
	printf("d: %ld in microsecs\n", feast->tt_sleep);
	printf("e: %ld times to eat\n", feast->n_meals);
}

