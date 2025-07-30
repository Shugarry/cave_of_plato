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
# include <errno.h>

typedef struct s_feast	t_feast;

typedef enum e_opt
{
	O_LOCK,
	O_UNLOCK,
	O_INIT,
	O_DESTROY,
	O_CREATE,
	O_JOIN,
	O_DETACH
}	t_opt;

typedef enum e_timecode
{
	SECOND,
	MILLISECOND,
	MICROSECOND
}	t_timecode;

typedef enum e_status
{
	EAT,
	SLEEP,
	THINK,
	DIE,
	TAKE_FORK_A,
	TAKE_FORK_B,
}	t_status;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	fork;
}	t_fork;

typedef struct s_plato
{
	int				id;
	int				n_meals;
	bool			full;
	long			time_lastmeal;
	t_fork			*fork_a;
	t_fork			*fork_b;
	pthread_mutex_t	mutex;
	pthread_t		thread_id;
	t_feast			*feast;
}	t_plato;

typedef struct s_feast
{
	long			n_philos;
	long			max_meals;
	long			tt_die;
	long			tt_eat;
	long			tt_sleep;
	t_list			*memlist;
	t_plato			*philos;
	t_fork			*forks;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	write_mutex;
	long			stopwatch;
	long			threads_running;
	bool			philosophers_ready;
	bool			dessert_time;
	pthread_t		monitor;
} t_feast;

// lists.c
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *node);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));

//memory.c
void	*memlist_alloc(t_feast *feast, size_t size);
void	*memlist_add(t_feast *feast, void *ptr);
void	memlist_free_ptr(t_feast *feast, void *ptr);

//helpers.c
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_atoi(const char *nptr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_bzero(void *s, size_t n);

// parsing.c
void	validate_and_parse(t_feast *feast, char **av);

// error.c
void	plato_exit(t_feast *feast, char *error_str, int error_num);
void	input_error(char *message);
void	debug_vars(t_feast *feast);

void	plato_exit(t_feast *feast, char *error_str, int error_num);

// threads.c
void	thread_handler(t_feast *feast, pthread_t *thread,
					void *(*func)(void *), void *data, t_opt option);
void	mutex_handler(t_feast *feast, pthread_mutex_t *mutex, t_opt option);

// getset.c
bool	get_bool(t_feast *feast, pthread_mutex_t *mutex, bool *var);
void	set_bool(t_feast *feast, pthread_mutex_t *mutex, bool *var, bool set_to);
long	get_long(t_feast *feast, pthread_mutex_t *mutex, long *var);
void	set_long(t_feast *feast, pthread_mutex_t *mutex, long *var, long set_to);
void	change_plato_status(t_plato *plato, t_status status);
void	increase_long(t_feast *feast, pthread_mutex_t *mutex, long *var);

// logic.c
void	ft_usleep(t_feast *feast, long usec);
long	get_time(t_feast *feast, t_timecode timecode);
void	start_feast(t_feast *feast);

#endif
