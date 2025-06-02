/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:48:56 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/02 18:06:52 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h>

# ifndef DEBUG
#  define DEBUG 0
# endif

# define THINKING 0
# define EATING 1
# define SLEEPING 2
# define FORK_TAKEN 3
# define DIED 4

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long			start_time;
	bool			simulation_end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	end_mutex;
	t_philo			*philos;
};

struct s_philo
{
	int				id;
	int				eat_count;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
};

// Initialization
int		init_data(t_data *data, int argc, char **argv);
int		init_mutexes(t_data *data);
int		init_philos(t_data *data);
int		ft_atoi(const char *str);

// Initialization utils
int		parse_optional_args(t_data *data, int argc, char **argv);
int		parse_time_settings(t_data *data, char **argv);
int		parse_philo_count(t_data *data, char *arg);
int		parse_positive_int(const char *str, int *out);

// Philosopher actions
void	*philo_routine(void *arg);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

// Monitoring
void	*monitor_routine(void *arg);
bool	check_if_dead(t_philo *philo);
bool	check_if_all_ate(t_data *data);

// Utilities
long	get_time_ms(void);
void	print_status(t_philo *philo, int status);
void	smart_sleep(long duration, t_data *data);
bool	get_simulation_end(t_data *data);
void	set_simulation_end(t_data *data);
void	debug_print_status(t_philo *philo, int status, const char *fmt, ...);

// Cleanup
void	cleanup(t_data *data);

//debug
void	print_debug(t_philo *philo, int status, pthread_mutex_t *fork);
void	print_meal_summary(t_data *data);

//debug_utils
void	print_thinking(t_philo *philo, long timestamp);
void	print_eating(t_philo *philo, long timestamp);
void	print_sleeping(t_philo *philo, long timestamp);
void	print_fork_taken(t_philo *philo, long timestamp, \
		pthread_mutex_t *fork);
void	print_died(t_philo *philo, long timestamp);

#endif