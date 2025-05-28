/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:48:56 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/28 14:14:54 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define RESET   "\033[0m"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_status;
typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;
typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;

}	t_fork;
typedef struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		philo_mutex;
	t_table		*table;

}	t_philo;

typedef struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals;
	long		start_simulation;
	bool		end_simulation;
	bool		all_threads_ready;
	long		thread_running_nb;
	pthread_t	monitor;
	t_mtx		table_mutex;
	t_mtx		write_lock;
	t_fork		*forks;
	t_philo		*philo;

}	t_table;
//error.c//
void	print_error(char *s);
int		check_error_input(char **av);
//utils.c//
long	ft_atoi(const char *str);
void	*safe_malloc(size_t bytes);
long	get_time(t_time_code time_code);
void	precise_usleep(long usec, t_table *table);
void	clean(t_table *table);
//int_var.c//
t_table	*init_var(char **av);
void	data_init(t_table *tbale);
//safe_mutex.c//
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	handle_mutex_error(int status, t_opcode opcode);
//safe_thread,c//
void	handle_thread_error(int status, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, \
		t_opcode opcode);
//dinner.c//
void	dinner_start(t_table *table);
void	eat(t_philo *philo);
void	thinking(t_philo *philo);
void	*lone_philo(void *arg);
//getter_setter.c//
bool	simulation_finished(t_table *table);
long	get_long(t_mtx *mutex, long *value);
void	set_long(t_mtx *mutex, long *dest, long value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_bool(t_mtx *mutex, bool *dest, bool value);
//synchro_utils.c//
void	wait_all_threads(t_table *table);
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
void	increase_long(t_mtx *mutex, long *value);
//write.c//
void	write_status(t_philo_status status, t_philo *philo);
//monitor.c//
void	*monitor_dinner(void *data);
bool	philo_died(t_philo *philo);

#endif