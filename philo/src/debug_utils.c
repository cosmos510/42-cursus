/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:03:08 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/02 12:36:40 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_thinking(t_philo *philo, long timestamp)
{
	printf("[DEBUG] %ld ms: Philosopher %d is thinking (meals eaten: %d)\n",
		timestamp, philo->id, philo->eat_count);
}

void	print_eating(t_philo *philo, long timestamp)
{
	int	left_id;
	int	right_id;

	left_id = philo->left_fork - philo->data->forks + 1;
	right_id = philo->right_fork - philo->data->forks + 1;
	printf("[DEBUG] %ld ms: Philosopher %d is eating meal #%d ",
		timestamp, philo->id, philo->eat_count + 1);
	printf("with forks %d and %d\n", left_id, right_id);
}

void	print_sleeping(t_philo *philo, long timestamp)
{
	printf("[DEBUG] %ld ms: Philosopher %d is sleeping after ",
		timestamp, philo->id);
	printf("eating %d meals\n", philo->eat_count);
}

void	print_fork_taken(t_philo *philo, long timestamp,
	pthread_mutex_t *fork)
{
	int	fork_id;

	fork_id = fork - philo->data->forks + 1;
	printf("[DEBUG] %ld ms: Philosopher %d has taken fork %d\n",
		timestamp, philo->id, fork_id);
}

void	print_died(t_philo *philo, long timestamp)
{
	long	current_time;

	printf("[DEBUG] %ld ms: Philosopher %d died after eating %d meals. ",
		timestamp, philo->id, philo->eat_count);
	if (philo->eat_count == 0)
		printf("Last meal: never\n");
	else
	{
		current_time = get_time_ms();
		printf("Last meal: %ld ms ago\n",
			current_time - philo->last_meal_time);
	}
}
