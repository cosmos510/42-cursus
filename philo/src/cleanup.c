/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:26:10 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/01 19:23:24 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	cleanup(t_data *data)
{
	int	i;

	if (data->philos)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(&data->philos[i].meal_mutex);
			i++;
		}
		free(data->philos);
	}
	if (data->forks)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->end_mutex);
}
