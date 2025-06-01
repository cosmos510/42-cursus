/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:02:30 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/01 19:15:48 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	debug_message(t_philo *philo, int status, long timestamp)
{
	if (status == THINKING)
		printf("[DEBUG] %ld ms: Philosopher %d is thinking (meals eaten: %d)\n",
			timestamp, philo->id, philo->eat_count);
	else if (status == EATING)
		printf("[DEBUG] %ld ms: Philosopher %d is eating meal #%d \
			with forks %p and %p\n", \
			timestamp, philo->id, philo->eat_count + 1,
			(void *)philo->left_fork, (void *)philo->right_fork);
	else if (status == SLEEPING)
		printf("[DEBUG] %ld ms: Philosopher %d is sleeping \
			after eating %d meals\n", \
			timestamp, philo->id, philo->eat_count);
	else if (status == FORK_TAKEN)
		printf("[DEBUG] %ld ms: Philosopher %d has taken fork %p\n",
			timestamp, philo->id, (void *)philo->left_fork);
	else if (status == DIED)
		printf("[DEBUG] %ld ms: Philosopher %d died after eating %d meals. \
			Last meal: %ld ms ago\n", \
			timestamp, philo->id, philo->eat_count,
			timestamp - philo->last_meal_time);
}

void	print_debug(t_philo *philo, int status)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (!get_simulation_end(philo->data))
	{
		timestamp = get_time_ms() - philo->data->start_time;
		debug_message(philo, status, timestamp);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}
