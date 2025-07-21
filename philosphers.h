#ifndef PHILOSPHERS_H
# define PHILOSPHERS_H

# include <pthread.h>
# include <bits/pthreadtypes.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>

typedef enum e_mutex_opt
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}	t_mutex_opt;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	fork;
	struct s_fork	*next;
}	t_fork;

typedef struct s_plato
{
	int				id;
	int				n_meals;
	bool			hungry;
	long			t_lastmeal;
	t_fork			*left;
	t_fork			*right;
	pthread_t		thread_id;
	struct s_plato	*next;
}	t_plato;

typedef struct s_dinnertable
{
	long	n_philos;
	long	n_meals;
	long	tt_die;
	long	tt_eat;
	long	tt_sleep;
	t_list	*memlist;
	t_plato	*philos;
	t_fork	*forks;
} t_dinnertable;

// lists.c
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *node);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));

//memory.c
void	*memlist_alloc(t_dinnertable *dinnertable, size_t size);
void	*memlist_add(t_dinnertable *dinnertable, void *ptr);
void	memlist_free_ptr(t_dinnertable *dinnertable, void *ptr);

//helpers.c
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_atoi(const char *nptr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_bzero(void *s, size_t n);

// parsing.c
void	validate_and_parse(t_dinnertable *dinnertable, char **av);

// error.c
void	plato_exit(t_dinnertable *dinnertable, char *error_str, int error_num);
void	input_error(char *message);
void	debug_vars(t_dinnertable *dinnertable);

void	plato_exit(t_dinnertable *dinnertable, char *error_str, int error_num);

#endif
