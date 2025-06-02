/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:02:33 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/02 18:03:09 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	parse_positive_int(const char *str, int *out)
{
	int	value;

	value = ft_atoi(str);
	if (value <= 0)
		return (1);
	*out = value;
	return (0);
}

int	parse_philo_count(t_data *data, char *arg)
{
	if (parse_positive_int(arg, &data->num_philos))
	{
		printf("Error: Invalid number of philosophers\n");
		return (1);
	}
	return (0);
}

int	parse_time_settings(t_data *data, char **argv)
{
	if (parse_positive_int(argv[2], &data->time_to_die))
	{
		printf("Error: Invalid time to die\n");
		return (1);
	}
	if (parse_positive_int(argv[3], &data->time_to_eat))
	{
		printf("Error: Invalid time to eat\n");
		return (1);
	}
	if (parse_positive_int(argv[4], &data->time_to_sleep))
	{
		printf("Error: Invalid time to sleep\n");
		return (1);
	}
	return (0);
}

int	parse_optional_args(t_data *data, int argc, char **argv)
{
	if (argc == 6)
	{
		if (parse_positive_int(argv[5], &data->must_eat_count))
		{
			printf("Error: Invalid number of times each philosopher must eat\n");
			return (1);
		}
	}
	else
		data->must_eat_count = -1;
	return (0);
}
