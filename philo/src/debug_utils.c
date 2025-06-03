/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:03:08 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/02 19:21:34 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_thinking(t_philo *philo, long timestamp)
{
	const char	*color;

	color = get_philo_color(philo->id);
	printf("%s[DEBUG] %ld ms: Philosopher %d is thinking \
		(meals eaten: %d)\n" COLOR_RESET, \
		color, timestamp, philo->id, philo->eat_count);
}

void	print_eating(t_philo *philo, long timestamp)
{
	const char	*color;
	int			left_id;
	int			right_id;

	color = get_philo_color(philo->id);
	left_id = philo->left_fork - philo->data->forks + 1;
	right_id = philo->right_fork - philo->data->forks + 1;
	printf("%s[DEBUG] %ld ms: Philosopher %d is eating meal \
		#%d with forks %d and %d\n" COLOR_RESET, \
		color, timestamp, philo->id, philo->eat_count + 1, left_id, right_id);
}

void	print_sleeping(t_philo *philo, long timestamp)
{
	const char	*color;

	color = get_philo_color(philo->id);
	printf("%s[DEBUG] %ld ms: Philosopher %d is sleeping \
		after eating %d meals\n" COLOR_RESET, \
		color, timestamp, philo->id, philo->eat_count);
}

void	print_fork_taken(t_philo *philo, long timestamp, pthread_mutex_t *fork)
{
	const char	*color;
	int			fork_id;

	color = get_philo_color(philo->id);
	fork_id = fork - philo->data->forks + 1;
	printf("%s[DEBUG] %ld ms: Philosopher %d has taken fork %d\n" COLOR_RESET,
		color, timestamp, philo->id, fork_id);
}

void	print_died(t_philo *philo, long timestamp)
{
	const char	*color;
	long		current_time;

	color = get_philo_color(philo->id);
	printf("%s[DEBUG] %ld ms: Philosopher %d died after eating %d meals. ",
		color, timestamp, philo->id, philo->eat_count);
	if (philo->eat_count == 0)
		printf("Last meal: never\n" COLOR_RESET);
	else
	{
		current_time = get_time_ms();
		printf("Last meal: %ld ms ago\n" COLOR_RESET,
			current_time - philo->last_meal_time);
	}
}
