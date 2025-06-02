/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:15:52 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/02 19:25:21 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static void	print_status_message(t_philo *philo, int status, \
	const char *color, long timestamp)
{
	if (status == THINKING)
		printf("%s%ld %d is thinking\n" COLOR_RESET, \
			color, timestamp, philo->id);
	else if (status == EATING)
		printf("%s%ld %d is eating\n" COLOR_RESET, \
			color, timestamp, philo->id);
	else if (status == SLEEPING)
		printf("%s%ld %d is sleeping\n" COLOR_RESET, \
			color, timestamp, philo->id);
	else if (status == FORK_TAKEN)
		printf("%s%ld %d has taken a fork\n" COLOR_RESET, \
			color, timestamp, philo->id);
	else if (status == DIED)
		printf("%s%ld %d died\n" COLOR_RESET, color, \
			timestamp, philo->id);
}

void	print_status(t_philo *philo, int status)
{
	long		timestamp;
	const char	*color;

	color = get_philo_color(philo->id);
	if (DEBUG && status != FORK_TAKEN)
		print_debug(philo, status, NULL);
	else if (!DEBUG)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		if (!get_simulation_end(philo->data))
		{
			timestamp = get_time_ms() - philo->data->start_time;
			print_status_message(philo, status, color, timestamp);
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
