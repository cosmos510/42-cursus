/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:02:30 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/02 19:22:36 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	debug_message(t_philo *philo, int status, long timestamp, \
	pthread_mutex_t *fork)
{
	if (status == THINKING)
		print_thinking(philo, timestamp);
	else if (status == EATING)
		print_eating(philo, timestamp);
	else if (status == SLEEPING)
		print_sleeping(philo, timestamp);
	else if (status == FORK_TAKEN)
		print_fork_taken(philo, timestamp, fork);
	else if (status == DIED)
		print_died(philo, timestamp);
}

void	print_debug(t_philo *philo, int status, pthread_mutex_t *fork)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (!get_simulation_end(philo->data))
	{
		timestamp = get_time_ms() - philo->data->start_time;
		debug_message(philo, status, timestamp, fork);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	print_meal_summary(t_data *data)
{
	int	i;

	printf(COLOR_MAGENTA "\n[DEBUG] === MEAL SUMMARY ===\n" COLOR_RESET);
	i = 0;
	while (i < data->num_philos)
	{
		printf(COLOR_WHITE "[DEBUG] Philosopher %d " \
			COLOR_GREEN "ate %d times\n" COLOR_RESET, \
			data->philos[i].id, data->philos[i].eat_count);
		i++;
	}
	printf(COLOR_MAGENTA "[DEBUG] ====================\n\n" COLOR_RESET);
}
