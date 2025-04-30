#ifndef PHILOSPHERS_H
# define PHILOSPHERS_H

#include "libft/libft.h"
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_plato
{
	int	id;
	struct s_plato *next;
} t_plato;

typedef struct s_dinnertable
{
	int		n_philos;
	int		n_meals;
	int		tt_die;
	int		tt_eat;
	int		tt_sleep;
	t_plato	*philos;
} t_dinnertable;

int		ft_atoi(const char *nptr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	free_exit(t_dinnertable *dinnertable, int status, char  *msg);

#endif
