/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:07:17 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/01 12:41:21 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
void	write_status(t_philo_status status, t_philo *philo)
{
	long		time;
	static bool	debug = DEBUG_MODE;

	time = get_time(MILLISECOND) - philo->table->start_simulation;
	if (simulation_finished(philo->table))
		return ;
	safe_mutex_handle(&philo->table->write_lock, LOCK);
	printf("%ld %d ", time, philo->id);
	if (status == TAKE_FIRST_FORK)
		printf("has taken a fork");
	else if (status == TAKE_SECOND_FORK)
		printf("has taken a fork");
	else if (status == EATING)
	{
		printf("is eating");
		if (debug)
			print_debug_philo_status(philo);
	}
	else if (status == SLEEPING)
		printf("is sleeping");
	else if (status == THINKING)
		printf("is thinking");
	else if (status == DIED)
		printf("died");
	printf("\n");
	safe_mutex_handle(&philo->table->write_lock, UNLOCK);
}
*/

static void	print_status_message(t_philo_status status, \
	t_philo *philo, bool debug)
{
	static const char	*status_messages[] = {
		"has taken a fork",
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"
	};

	printf("%s", status_messages[status]);
	if (debug && status == EATING)
		print_debug_philo_status(philo);
}

void	write_status(t_philo_status status, t_philo *philo)
{
	long		time;
	static bool	debug = DEBUG_MODE;

	time = get_time(MILLISECOND) - philo->table->start_simulation;
	if (simulation_finished(philo->table))
		return ;
	safe_mutex_handle(&philo->table->write_lock, LOCK);
	printf("%ld %d ", time, philo->id);
	print_status_message(status, philo, debug);
	printf("\n");
	safe_mutex_handle(&philo->table->write_lock, UNLOCK);
}
