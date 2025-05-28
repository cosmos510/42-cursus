/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:34:21 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/28 14:06:56 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	philo_died(t_philo *philo)
{
	long	elpased;
	long	t_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elpased = get_time(MILLISECOND) - \
		get_long(&philo->philo_mutex, &philo->last_meal_time);
	t_to_die = philo->table->time_to_die / 1e3;
	if (elpased > t_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex, \
		&table->thread_running_nb, table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (--i < table->philo_nbr && !simulation_finished(table))
		{
			if (philo_died(table->philo + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				write_status(DIED, table->philo + i);
			}
		}
	}
	return (NULL);
}
