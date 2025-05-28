/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:07:17 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/28 13:11:36 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = get_time(MILLISECOND) - philo->table->start_simulation;
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->table->write_lock, LOCK);
	if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status) \
		&& !simulation_finished(philo->table))
		printf("%-ld %d has taken a fork\n", elapsed, philo->id);
	else if (EATING == status && !simulation_finished(philo->table))
		printf("%-ld %d is eating\n", elapsed, philo->id);
	else if (SLEEPING == status && !simulation_finished(philo->table))
		printf("%-ld %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status && !simulation_finished(philo->table))
		printf("%-ld %d is thinking\n", elapsed, philo->id);
	else if (DIED == status)
		printf("%-ld %d died\n", elapsed, philo->id);
	safe_mutex_handle(&philo->table->write_lock, UNLOCK);
}
