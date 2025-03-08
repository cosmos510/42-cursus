/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 12:46:14 by cosmos            #+#    #+#             */
/*   Updated: 2025/01/02 22:31:22 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_map(char **map, t_map *pos)
{
	if (!check_c(map, pos))
	{
		ft_printf("Error\nNo collectible found, map error\n");
		return (0);
	}
	if (!check_e(map))
	{
		ft_printf("Error\nNo exit or more than one exit found\n");
		return (0);
	}
	if (!check_p(map))
	{
		ft_printf("Error\nNo player or more than one player found\n");
		return (0);
	}
	if (!check_surrender_wall(map))
	{
		ft_printf("Error\nNo suurender by wall\n");
		return (0);
	}
	return (1);
}

int	check_surrender_wall(char **map)
{
	int		y;
	int		x;
	int		height;
	size_t	len_map;

	y = 0;
	x = 0;
	height = 0;
	len_map = ft_strlen(map[0]);
	while (map[height])
		height++;
	while (map[0][x])
	{
		if (map[0][x] != '1' || map[height - 1][x] != '1')
			return (0);
		x++;
	}
	while (map[y])
	{
		if (map[y][0] != '1' || map[y][len_map - 1] != '1' || \
		ft_strlen(map[y]) != len_map)
			return (0);
		y++;
	}
	return (1);
}

int	check_e(char **map)
{
	int		y;
	int		x;
	int		count_e;

	count_e = 0;
	x = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'E')
				count_e += 1;
			x++;
		}
		y++;
	}
	if (count_e != 1)
		return (0);
	return (1);
}

int	check_c(char **map, t_map *pos)
{
	int	y;
	int	x;
	int	count_c;

	count_c = 0;
	x = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'C')
				count_c += 1;
			x++;
		}
		y++;
	}
	if (count_c < 1)
		return (0);
	pos->collectibles = count_c;
	pos->col_game = count_c;
	return (1);
}

int	check_p(char **map)
{
	int	y;
	int	x;
	int	count_p;

	count_p = 0;
	x = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
				count_p += 1;
			x++;
		}
		y++;
	}
	if (count_p != 1)
		return (0);
	return (1);
}
