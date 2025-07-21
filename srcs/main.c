#include "../philosphers.h"

void	init_philo_list(t_dinnertable *dinnertable)
{
	int	i;
	t_plato *tmp;
	
	i = dinnertable->n_philos - 1;
	while (i >= 0)
	{
		tmp = memlist_alloc(dinnertable, sizeof(t_plato));
		tmp->id = i;
		tmp->next = dinnertable->philos;
		dinnertable->philos = tmp;
		i--;
	}
	tmp = dinnertable->philos;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = dinnertable->philos;
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
	int i = 0;
	for (t_plato *node = dinnertable.philos; node; node = node->next)
	{
		if (i > dinnertable.n_philos)
			break;
		printf("node: %d, philo: %d\n", i, node->id);
		i++;
	}
	plato_exit(&dinnertable, NULL, EXIT_SUCCESS);
}
