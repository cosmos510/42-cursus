/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:34:21 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/02 11:49:30 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	check_if_dead(t_philo *philo)
{
	long	current_time;
	long	last_meal;

	pthread_mutex_lock(&philo->meal_mutex);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	current_time = get_time_ms();
	if (current_time - last_meal > philo->data->time_to_die)
	{
		print_status(philo, DIED);
		set_simulation_end(philo->data);
		return (true);
	}
	return (false);
}

bool	check_if_all_ate(t_data *data)
{
	int	i;
	int	count;

	if (data->must_eat_count == -1)
		return (false);
	i = 0;
	count = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		if (data->philos[i].eat_count >= data->must_eat_count)
			count++;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		i++;
	}
	if (count == data->num_philos)
	{
		set_simulation_end(data);
		return (true);
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!get_simulation_end(data))
	{
		i = 0;
		while (i < data->num_philos && !get_simulation_end(data))
		{
			if (check_if_dead(&data->philos[i]))
				break ;
			i++;
		}
		if (get_simulation_end(data) || check_if_all_ate(data))
		{
			if (DEBUG)
				print_meal_summary(data);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
