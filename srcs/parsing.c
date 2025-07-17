/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:56:01 by frey-gal          #+#    #+#             */
/*   Updated: 2025/07/17 17:58:22 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosphers.h"

static bool	is_numeric(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[0] != '+' && str[0] != '-')
			return (false);
		i++;
	}
	return (true);
}

static bool	in_bounds(char	*str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] == 0)
		i++;
	if (ft_strlen(str) > 10)
		return (false);
	if (ft_atoi(str) < 1)
		return (false);
	return (true);
}

static void	parse_args(t_dinnertable *dinnertable, char **av)
{
	dinnertable->n_philos = ft_atoi(av[1]);
	dinnertable->tt_die = ft_atoi(av[2]);
	dinnertable->tt_eat = ft_atoi(av[3]);
	dinnertable->tt_sleep = ft_atoi(av[4]);
	if (av[5])
		dinnertable->n_meals = ft_atoi(av[5]);
}

void	validate_and_parse(t_dinnertable *dinnertable, char **av)
{
	int	i;

	i = 1;
	while (av && av[i])
	{
		if (is_numeric(av[i]) == false || in_bounds(av[i]) == false)
			input_error();
		i++;
	}
	parse_args(dinnertable, av);
}
