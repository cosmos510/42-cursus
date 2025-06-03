/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:12:04 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/02 19:22:24 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

char	*get_philo_color(int id)
{
	int	index;

	index = (id - 1) % 7;
	if (index == 0)
		return (COLOR_RED);
	else if (index == 1)
		return (COLOR_GREEN);
	else if (index == 2)
		return (COLOR_YELLOW);
	else if (index == 3)
		return (COLOR_BLUE);
	else if (index == 4)
		return (COLOR_MAGENTA);
	else if (index == 5)
		return (COLOR_CYAN);
	else
		return (COLOR_WHITE);
}
