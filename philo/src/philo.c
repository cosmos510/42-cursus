/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:22:28 by maximemarti       #+#    #+#             */
/*   Updated: 2025/05/27 18:40:22 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	validate_args(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		print_error(NULL);
		return (0);
	}
	if (check_error_input(av) == 1)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_table	*table;

	if (!validate_args(ac, av))
		return (1);
	table = init_var(av);
	if (!table)
		return (1);
	data_init(table);
	return (0);
}
