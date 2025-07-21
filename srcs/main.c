#include "../philosphers.h"

void	set_forks(t_dinnertable *dinnertable, t_plato *plato, int pos)
{
	int	l_pos;
	int	r_pos;

	r_pos = pos;
	l_pos = pos - 1;
	if (l_pos < 0)
		l_pos += dinnertable->n_philos;
	plato->left = &dinnertable->forks[l_pos];
	plato->right = &dinnertable->forks[r_pos];
}

void	init_philo_list(t_dinnertable *dinnertable)
{
	int	i;

	i = 0;
	dinnertable->philos = memlist_alloc(dinnertable,
									 sizeof(t_plato) * dinnertable->n_philos);
	while (i < dinnertable->n_philos)
	{
		ft_bzero(&dinnertable->philos[i], sizeof(t_plato));
		dinnertable->philos[i].id = i;
		set_forks(dinnertable, &dinnertable->philos[i], i);
		i++;
	}
}

void	init_fork_list(t_dinnertable *dinnertable)
{
	int	i;

	i = 0;
	dinnertable->forks = memlist_alloc(dinnertable,
									 sizeof(t_fork) * dinnertable->n_philos);
	while (i < dinnertable->n_philos)
	{
		ft_bzero(&dinnertable->forks[i], sizeof(t_plato));
		mutex_handler(dinnertable, &dinnertable->forks[i].fork, INIT);
		dinnertable->forks[i].id = i;
		i++;
	}
}

int main(int ac, char **av)
{
	t_dinnertable	dinnertable;

	if (ac != 6 && ac != 5)
		input_error("Incorrect argument amount");
	ft_bzero(&dinnertable, sizeof(t_dinnertable));
	validate_and_parse(&dinnertable, av);
	init_fork_list(&dinnertable);
	init_philo_list(&dinnertable);
	for (int i = 0; i < dinnertable.n_philos; i++)
	{
		t_plato tmp = dinnertable.philos[i];
		printf("Plato %d: lf: %d, rf: %d\n", tmp.id, tmp.left->id, tmp.right->id);
	}
	debug_vars(&dinnertable);
	plato_exit(&dinnertable, NULL, EXIT_SUCCESS);
}
