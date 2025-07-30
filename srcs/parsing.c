/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:56:01 by frey-gal          #+#    #+#             */
/*   Updated: 2025/07/29 18:37:00 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

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

static void	parse_args(t_feast *feast, char **av)
{
	feast->n_philos = (long)ft_atoi(av[1]);
	feast->tt_die = (long)ft_atoi(av[2]) * 1e3;
	feast->tt_eat = (long)ft_atoi(av[3]) * 1e3;
	feast->tt_sleep = (long)ft_atoi(av[4]) * 1e3;
	if (av[5])
		feast->max_meals = (long)ft_atoi(av[5]);
	else
		feast->max_meals = -1;
}

void	validate_and_parse(t_feast *feast, char **av)
{
	int	i;

	i = 1;
	while (av && av[i])
	{
		if (is_numeric(av[i]) == false || in_bounds(av[i]) == false)
			input_error("Argument options are out of bounds or non-numeric");
		i++;
	}
	parse_args(feast, av);
}
