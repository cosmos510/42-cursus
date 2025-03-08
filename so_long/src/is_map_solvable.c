/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_solvable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 17:08:47 by cosmos            #+#    #+#             */
/*   Updated: 2025/01/06 11:35:36 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	is_map_solvable(char **map, t_map *pos)
{
	int		x_start;
	int		y_start;
	char	**new_map;

	x_start = find_x_start(map);
	y_start = find_y_start(map);
	pos->p_x_start = x_start;
	pos->p_y_start = y_start;
	check_map_size(map, pos);
	new_map = dup_map(pos->map, pos->y_map_size);
	if (!new_map)
		return (1);
	if (explore_map(pos, x_start, y_start, new_map) != 1)
	{
		ft_printf("The map is not solvable\n");
		free_map(new_map);
		return (1);
	}
	free_map(new_map);
	return (0);
}

int	check_map_size(char **map, t_map *pos)
{
	int	x_map_size;
	int	y_map_size;

	x_map_size = ft_strlen(map[0]);
	y_map_size = 0;
	while (map[y_map_size])
		y_map_size++;
	pos->x_map_size = x_map_size - 1;
	pos->y_map_size = y_map_size - 1;
	return (0);
}

int	explore_map(t_map *pos, int x_start, int y_start, char **map)
{
	int	path_found;

	if (x_start < 0 || y_start < 0 || x_start > pos->x_map_size \
	|| y_start > pos->y_map_size)
		return (0);
	if (map[y_start][x_start] == 'E')
		pos->exit_found = 1;
	if (map[y_start][x_start] == '1' || map[y_start][x_start] == 'V' \
	|| map[y_start][x_start] == 'S' || map[y_start][x_start] == 'E')
		return (0);
	if (map[y_start][x_start] == 'C')
		pos->collectibles--;
	if (pos->exit_found == 1 && pos->collectibles == 0)
		return (1);
	map[y_start][x_start] = 'V';
	path_found = 0;
	path_found = explore_map(pos, x_start + 1, y_start, map);
	if (!path_found)
		path_found = explore_map(pos, x_start - 1, y_start, map);
	if (!path_found)
		path_found = explore_map(pos, x_start, y_start + 1, map);
	if (!path_found)
		path_found = explore_map(pos, x_start, y_start - 1, map);
	return (path_found);
}

int	find_y_start(char **map)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
				return (y);
			x++;
		}
		y++;
	}
	return (-1);
}

int	find_x_start(char **map)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
				return (x);
			x++;
		}
		y++;
	}
	return (-1);
}
