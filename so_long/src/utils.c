/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:28:08 by cosmos            #+#    #+#             */
/*   Updated: 2025/01/06 12:33:31 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	render_move_bonus(t_map *pos)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_itoa(pos->move_count);
	pos->move_bonus = ft_strjoin("Moves: ", tmp);
	mlx_string_put(pos->mlx, pos->win, 50, 50, 0xFFFFFF, pos->move_bonus);
	mlx_string_put(pos->mlx, pos->win, 50 + 1, 50, 0xFFFFFF, pos->move_bonus);
	mlx_string_put(pos->mlx, pos->win, 50, 50 + 1, 0xFFFFFF, pos->move_bonus);
	mlx_string_put(pos->mlx, pos->win, 50 + 1, 50 + 1, \
	0xFFFFFF, pos->move_bonus);
	free(tmp);
	free(pos->move_bonus);
	return (0);
}

void	handle_exit(t_map *pos, int x, int y)
{
	if (pos->col_game == 0)
	{
		mlx_put_image_to_window(pos->mlx, pos->win, pos->img.exit_o, \
	x * pos->img_width, y * pos->img_height);
	}
	else
	{
		mlx_put_image_to_window(pos->mlx, pos->win, pos->img.exit, \
	x * pos->img_width, y * pos->img_height);
	}
}

void	handle_p(t_map *pos, int x, int y)
{
	if (pos->last_dir == 'r')
		mlx_put_image_to_window(pos->mlx, pos->win, pos->img.player_r, \
				x * pos->img_width, y * pos->img_height);
	if (pos->last_dir == 'l')
		mlx_put_image_to_window(pos->mlx, pos->win, pos->img.player, \
				x * pos->img_width, y * pos->img_height);
}

void	handle_item(t_map *pos, int x, int y)
{
	while (pos->map[y])
	{
		x = 0;
		while (pos->map[y][x])
		{
			if (pos->map[y][x] == '1')
				mlx_put_image_to_window(pos->mlx, pos->win, pos->img.wall, \
				x * pos->img_width, y * pos->img_height);
			else if (pos->map[y][x] == '0')
				mlx_put_image_to_window(pos->mlx, pos->win, \
				pos->img.background, x * pos->img_width, y * pos->img_height);
			else if (pos->map[y][x] == 'C')
				mlx_put_image_to_window(pos->mlx, pos->win, pos->img.coll, \
				x * pos->img_width, y * pos->img_height);
			else if (pos->map[y][x] == 'P')
				handle_p(pos, x, y);
			else if (pos->map[y][x] == 'S')
				mlx_put_image_to_window(pos->mlx, pos->win, \
				pos->img.enemy, x * pos->img_width, y * pos->img_height);
			else if (pos->map[y][x] == 'E')
				handle_exit(pos, x, y);
			x++;
		}
		y++;
	}
}
