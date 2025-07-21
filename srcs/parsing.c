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
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	in_bounds(char	*str)
{
	int	i;

	i = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	if (ft_strlen(str + i) > 10)
		return (false);
	if (ft_atoi(str) < 1)
		return (false);
	return (true);
}

static void	parse_args(t_dinnertable *dinnertable, char **av)
{
	dinnertable->n_philos = (long)ft_atoi(av[1]);
	dinnertable->tt_die = (long)ft_atoi(av[2]) * 1e3;
	dinnertable->tt_eat = (long)ft_atoi(av[3]) * 1e3;
	dinnertable->tt_sleep = (long)ft_atoi(av[4]) * 1e3;
	if (av[5])
		dinnertable->n_meals = (long)ft_atoi(av[5]);
	else
		dinnertable->n_meals = -1;
	if (dinnertable->tt_die < 6e4 || dinnertable->tt_eat < 6e4
		|| dinnertable->tt_sleep < 6e4)
		input_error("Argument options are out of bounds");

}

void	validate_and_parse(t_dinnertable *dinnertable, char **av)
{
	int	i;

	i = 1;
	while (av && av[i])
	{
		if (is_numeric(av[i]) == false || in_bounds(av[i]) == false)
			input_error("Argument options are out of bounds or non-numeric");
		i++;
	}
	parse_args(dinnertable, av);
}
