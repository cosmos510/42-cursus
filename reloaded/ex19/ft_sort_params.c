/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 18:13:22 by maximemarti       #+#    #+#             */
/*   Updated: 2024/09/21 19:27:16 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c);

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1 && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	**ft_sort_param(int ac, char *av[])
{
	int		i;
	int		j;
	char	*temp;

	i = 1;
	j = 1;
	while (i + 1 < ac)
	{
		j = 1;
		while (j < ac - i)
		{
			if (ft_strcmp(av[j], av[j + 1]) > 0)
			{
				temp = av[j];
				av[j] = av[j +1];
				av[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	return (av);
}

int	main(int ac, char *av[])
{
	int	i;

	i = 1;
	ft_sort_param(ac, av);
	while (i < ac)
	{
		ft_putstr(av[i]);
		ft_putstr("\n");
		i++;
	}
}
