/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:05:00 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/27 18:32:00 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_error(char *error)
{
	if (!error)
	{
		printf(RED "Error: Invalid arguments.\n" RESET);
		printf(YELLOW "Usage: " RESET "./philo ");
		printf(CYAN "number_of_philosophers time_to_die \
		time_to_eat time_to_sleep \
		[number_of_times_each_philosopher_must_eat]\n" RESET);
		printf(MAGENTA "All arguments must be positive \
		integers. The last argument is optional.\n" RESET);
		return ;
	}
	printf(RED "Error: Invalid arguments.\n" RESET);
	printf(CYAN "%s\n"RESET, error);
}

int	check_error_input(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) <= 0)
		{
			print_error(NULL);
			return (1);
		}
		i++;
	}
	return (0);
}
