/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:46:21 by frey-gal          #+#    #+#             */
/*   Updated: 2025/04/30 18:23:39 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosphers.h"
#include <stdio.h>
#include <stdlib.h>

void	init_dinner(t_dinnertable *dinnertable, int ac, char **av)
{
	dinnertable->n_philos = ft_atoi(av[1]);
	dinnertable->tt_die = ft_atoi(av[2]);
	dinnertable->tt_eat = ft_atoi(av[3]);
	dinnertable->tt_sleep = ft_atoi(av[4]);
	dinnertable->n_meals = -1;
	if (ac == 6)
		dinnertable->n_meals = ft_atoi(av[5]);
}

bool	check_args(char **av)
{
	while(*av)
	{
		++*av;
		if (!av || !*av || !**av)
			return (false);
		while (**av)
		{
			if (!(**av >= '0' && **av <= '9') && (**av != '-') && (**av != '+'))
				return (false);
			++**av;
		}
	}
	return (true);
}

void validation(t_dinnertable *dinnertable, int ac, char **av)
{
	if (!check_args(av))
		free_exit(dinnertable, EXIT_FAILURE, "Error: invalid args\n");
}

int main(int ac, char **av)
{
	t_dinnertable	dinnertable;

	if (ac != 5 && ac != 6)
	{
		printf("Invalid args, format: ./philosphers a b c d e\n");
		printf("a: (int)number of philosophers\n");
		printf("b: (int)time to die\n");
		printf("c: (int)time to eat\n");
		printf("d: (int)time to sleep\n");
		printf("e: (int)number of times philosophers must eat (optional)\n");
		free_exit(&dinnertable, EXIT_FAILURE, NULL);
	}

	validation(&dinnertable, ac, av);
	init_dinner(&dinnertable, ac, av);
}
