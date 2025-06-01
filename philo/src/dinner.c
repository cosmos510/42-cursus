/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:10:23 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/01 19:19:15 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, FORK_TAKEN);
	if (philo->data->num_philos == 1)
	{
		smart_sleep(philo->data->time_to_die, philo->data);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, FORK_TAKEN);
	print_status(philo, EATING);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time_ms();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
	smart_sleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, SLEEPING);
	smart_sleep(philo->data->time_to_sleep, philo->data);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, THINKING);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat / 2);
	while (!get_simulation_end(philo->data))
	{
		philo_eat(philo);
		if (get_simulation_end(philo->data) || \
				(philo->data->must_eat_count != -1 && \
				philo->eat_count >= philo->data->must_eat_count))
			break ;
		philo_sleep(philo);
		if (get_simulation_end(philo->data))
			break ;
		philo_think(philo);
	}
	return (NULL);
}
