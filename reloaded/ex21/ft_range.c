/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 21:48:07 by maximemarti       #+#    #+#             */
/*   Updated: 2024/09/21 22:02:09 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	*tab;
	int	size;
	int	i;

	i = 0;
	size = max - min;
	tab = malloc(sizeof(int) * size);
	if (tab == NULL)
		return (NULL);
	if (min >= max)
	{
		tab = NULL;
		return (tab);
	}
	while (min < max)
	{
		tab[i] = min;
		i++;
		min++;
	}
	return (tab);
}
