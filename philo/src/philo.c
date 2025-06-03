/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:22:28 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/02 19:00:34 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	validate_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf(COLOR_GREEN "Usage: " COLOR_RESET);
		printf(COLOR_CYAN "%s " COLOR_RESET, argv[0]);
		printf(COLOR_YELLOW "number_of_philosophers " COLOR_RESET);
		printf(COLOR_BLUE "time_to_die " COLOR_RESET);
		printf(COLOR_MAGENTA "time_to_eat " COLOR_RESET);
		printf(COLOR_RED "time_to_sleep " COLOR_RESET);
		printf(COLOR_WHITE "[number_of_times_each_philosopher_must_eat]\n" \
			COLOR_RESET);
		return (1);
	}
	return (0);
}

static int	initialize_simulation(t_data *data, int argc, char **argv)
{
	int	i;

	if (init_data(data, argc, argv) != 0 || init_mutexes(data) != 0 \
			|| init_philos(data) != 0)
	{
		cleanup(data);
		return (1);
	}
	data->start_time = get_time_ms();
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		i++;
	}
	return (0);
}

static int	create_threads(t_data *data, pthread_t *monitor)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, \
			philo_routine, &data->philos[i]) != 0)
		{
			set_simulation_end(data);
			return (1);
		}
	}
	if (pthread_create(monitor, NULL, monitor_routine, data) != 0)
	{
		set_simulation_end(data);
		return (1);
	}
	return (0);
}

static void	join_threads(t_data *data, pthread_t monitor)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
		pthread_join(data->philos[i].thread, NULL);
	pthread_join(monitor, NULL);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor;

	if (validate_args(argc, argv) != 0)
		return (1);
	if (initialize_simulation(&data, argc, argv) != 0)
		return (1);
	if (create_threads(&data, &monitor) != 0)
		return (1);
	join_threads(&data, monitor);
	cleanup(&data);
	return (0);
}
