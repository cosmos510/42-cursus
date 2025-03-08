/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmarti <maxmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 00:59:44 by cosmos            #+#    #+#             */
/*   Updated: 2024/12/19 08:29:41 by maxmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_strcmp(char *s1, char *s2)
{
	if (*s1 == '+')
	{
		if (*s2 != '+')
			s1++;
	}
	else
	{
		if (*s2 == '+')
			s2++;
	}
	while (*s1 == *s2 && *s1)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	ft_putstr(char *s)
{
	while (*s)
	{
		write(1, &*s, 1);
		s++;
	}
}

char	**split_input(int ac, char **av)
{
	char	**tmp;

	if (ac == 2)
	{
		tmp = ft_split(av[1], ' ');
		return (tmp);
	}
	return (av + 1);
}
