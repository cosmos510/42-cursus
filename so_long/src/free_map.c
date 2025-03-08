/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:13:16 by cosmos            #+#    #+#             */
/*   Updated: 2025/01/05 20:36:24 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
	map = NULL;
}

void	exit_clean(char **map)
{
	free_map(map);
}

int	close_it(t_map *pos, int exit_i)
{
	destroy_mlx(pos);
	exit_clean(pos->map);
	if (pos->mlx)
		free(pos->mlx);
	if (exit_i == 1)
		exit(1);
	exit(EXIT_SUCCESS);
	return (0);
}

void	destroy_mlx(t_map *pos)
{
	if (pos->win)
		mlx_destroy_window(pos->mlx, pos->win);
	if (pos->img.background)
		mlx_destroy_image(pos->mlx, pos->img.background);
	if (pos->img.wall)
		mlx_destroy_image(pos->mlx, pos->img.wall);
	if (pos->img.coll)
		mlx_destroy_image(pos->mlx, pos->img.coll);
	if (pos->img.exit)
		mlx_destroy_image(pos->mlx, pos->img.exit);
	if (pos->img.exit_o)
		mlx_destroy_image(pos->mlx, pos->img.exit_o);
	if (pos->img.player)
		mlx_destroy_image(pos->mlx, pos->img.player);
	if (pos->img.player_r)
		mlx_destroy_image(pos->mlx, pos->img.player_r);
	if (pos->img.empty_space)
		mlx_destroy_image(pos->mlx, pos->img.empty_space);
	if (pos->img.enemy)
		mlx_destroy_image(pos->mlx, pos->img.enemy);
	if (pos->mlx)
		mlx_destroy_display(pos->mlx);
}
