#include "../philosphers.h"

void	init_dinner(t_dinnertable *dinnertable, int ac, char **av)
{
	if (ac == 6)
		dinnertable->n_meals = atoi(av[5]);
	dinnertable->n_philos;
	dinnertable->tt_die;
	dinnertable->tt_eat;
	dinnertable->tt_sleep;
}

int main(int ac, char **av)
{
	t_dinnertable	dinnertable;

	if (ac != 6 || ac != 5)
	{
		printf("Invalid args, format: ./philosphers a b c d e\n");
		printf("a: number of philosophers\n");
		printf("b: time to die\n");
		printf("c: time to eat\n");
		printf("d: time to sleep\n");
		printf("e: number of times philosophers must eat (optional)\n");
		exit(EXIT_FAILURE);
	}

	init_dinner(&dinnertable);
}
