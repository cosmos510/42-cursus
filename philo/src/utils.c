/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:15:52 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/28 14:47:15 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	ft_atoi(const char *str)
{
	long		i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		print_error("Error with the malloc");
	return (ret);
}

long	get_time(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		print_error("Get time of the day failed");
	if (SECOND == time_code)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (MILLISECOND == time_code)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (MICROSECOND == time_code)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	else
		print_error("Wrong input to get time");
	return (42);
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapse;
	long	remaining;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapse = get_time(MICROSECOND) - start;
		remaining = usec - elapse;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
		{
			while (get_time(MICROSECOND) - start < usec)
				;
		}
	}
}

void	clean(t_table *table)
{
	t_philo *philo;
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philo + i;
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
		safe_mutex_handle(&table->forks[i].fork, DESTROY);
	}
	safe_mutex_handle(&table->write_lock, DESTROY);
	safe_mutex_handle(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philo);
	free(table);
}