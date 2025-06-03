/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:06:17 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/02 18:05:01 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	int			result;
	int			sign;
	const char	*start;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	start = str;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!(*str >= '0' && *str <= '9'))
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0' || str == start)
		return (-1);
	return (result * sign);
}

int	parse_args(t_data *data, int argc, char **argv)
{
	if (parse_philo_count(data, argv[1]))
		return (1);
	if (parse_time_settings(data, argv))
		return (1);
	if (parse_optional_args(data, argc, argv))
		return (1);
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	memset(data, 0, sizeof(t_data));
	data->simulation_end = false;
	if (parse_args(data, argc, argv))
		return (1);
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->end_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].last_meal_time = get_time_ms();
		data->philos[i].data = data;
		if (pthread_mutex_init(&data->philos[i].meal_mutex, NULL) != 0)
			return (1);
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		i++;
	}
	return (0);
}
