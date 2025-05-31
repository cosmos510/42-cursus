/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:06:17 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/31 12:42:00 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_table	*init_var(char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->philo_nbr = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (table->time_to_die < 60 || table->time_to_eat < 60 \
	|| table->time_to_sleep < 60)
	{
		print_error("Use time stamp major than 60ms");
		free(table);
		return (NULL);
	}
	if (av[5])
		table->nbr_limit_meals = ft_atoi(av[5]);
	else
		table->nbr_limit_meals = -1;
	return (table);
}

void	assign_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	int	philo_nb;

	philo_nb = philo->table->philo_nbr;
	if (philo_pos < (philo_pos + 1) % philo_nb)
	{
		philo->first_fork = &forks[philo_pos];
		philo->second_fork = &forks[(philo_pos + 1) % philo_nb];
	}
	else
	{
		philo->first_fork = &forks[(philo_pos + 1) % philo_nb];
		philo->second_fork = &forks[philo_pos];
	}
}

void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philo + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		safe_mutex_handle(&philo->philo_mutex, INIT);
		assign_forks(philo, table->forks, i);
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->thread_running_nb = 0;
	table->philo = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	safe_mutex_handle(&table->table_mutex, INIT);
	safe_mutex_handle(&table->write_lock, INIT);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	while (++i < table->philo_nbr)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}
