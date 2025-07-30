/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:34:58 by frey-gal          #+#    #+#             */
/*   Updated: 2025/07/30 07:36:06 by frey-gal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	set_forks(t_feast *feast, t_plato *plato, int pos)
{
	int	l_pos;
	int	r_pos;

	r_pos = pos;
	l_pos = pos - 1;
	if (l_pos < 0)
		l_pos += feast->n_philos;
	if (pos % 2 == 0)
	{
		plato->fork_a = &feast->forks[l_pos];
		plato->fork_b = &feast->forks[r_pos];
	}
	else
	{
		plato->fork_a = &feast->forks[r_pos];
		plato->fork_b = &feast->forks[l_pos];
	}
}

void	init_philo_list(t_feast *feast)
{
	int	i;

	i = 0;
	feast->philos = memlist_alloc(feast, sizeof(t_plato) * feast->n_philos);
	while (i < feast->n_philos)
	{
		ft_bzero(&feast->philos[i], sizeof(t_plato));
		feast->philos[i].id = i;
		feast->philos[i].feast = feast;
		mutex_handler(feast, &feast->philos[i].mutex, O_INIT);
		set_forks(feast, &feast->philos[i], i);
		i++;
	}
}

void	init_fork_list(t_feast *feast)
{
	int	i;

	i = 0;
	feast->forks = memlist_alloc(feast, sizeof(t_fork) * feast->n_philos);
	while (i < feast->n_philos)
	{
		ft_bzero(&feast->forks[i], sizeof(t_fork));
		mutex_handler(feast, &feast->forks[i].fork, O_INIT);
		feast->forks[i].id = i;
		i++;
	}
}

void	init_table(t_feast *feast)
{
	ft_bzero(feast, sizeof(t_feast));
	mutex_handler(feast, &feast->data_mutex, O_INIT);
	mutex_handler(feast, &feast->write_mutex, O_INIT);
}

int main(int ac, char **av)
{
	t_feast	feast;

	if (ac != 6 && ac != 5)
		input_error("Incorrect argument amount");
	init_table(&feast);
	validate_and_parse(&feast, av);
	init_fork_list(&feast);
	init_philo_list(&feast);
	start_feast(&feast);
	//debug_vars(&feast);
	plato_exit(&feast, NULL, EXIT_SUCCESS);
}
