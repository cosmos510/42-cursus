/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:15:52 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/02 11:59:52 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_status(t_philo *philo, int status)
{
	long	timestamp;

	if (DEBUG && status != FORK_TAKEN)
		print_debug(philo, status, NULL);
	else if (!DEBUG)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		if (!get_simulation_end(philo->data))
		{
			timestamp = get_time_ms() - philo->data->start_time;
			if (status == THINKING)
				printf("%ld %d is thinking\n", timestamp, philo->id);
			else if (status == EATING)
				printf("%ld %d is eating\n", timestamp, philo->id);
			else if (status == SLEEPING)
				printf("%ld %d is sleeping\n", timestamp, philo->id);
			else if (status == FORK_TAKEN)
				printf("%ld %d has taken a fork\n", timestamp, philo->id);
			else if (status == DIED)
				printf("%ld %d died\n", timestamp, philo->id);
		}
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
}

void	smart_sleep(long duration, t_data *data)
{
	long	start;
	long	current;

	start = get_time_ms();
	while (!get_simulation_end(data))
	{
		current = get_time_ms();
		if (current - start >= duration)
			break ;
		usleep(500);
	}
}

bool	get_simulation_end(t_data *data)
{
	bool	end;

	pthread_mutex_lock(&data->end_mutex);
	end = data->simulation_end;
	pthread_mutex_unlock(&data->end_mutex);
	return (end);
}

void	set_simulation_end(t_data *data)
{
	pthread_mutex_lock(&data->end_mutex);
	data->simulation_end = true;
	pthread_mutex_unlock(&data->end_mutex);
}
