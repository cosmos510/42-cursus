/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 09:48:36 by cosmos            #+#    #+#             */
/*   Updated: 2025/01/05 20:24:53 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	load_img(t_map *pos)
{
	pos->img.background = init_img(pos, "textures/background.xpm", \
	&pos->img.background_data);
	pos->img.wall = init_img(pos, "textures/wall.xpm", \
	&pos->img.wall_data);
	pos->img.coll = init_img(pos, "textures/collectible.xpm", \
	&pos->img.coll_data);
	pos->img.exit = init_img(pos, "textures/exit.xpm", \
	&pos->img.exit_data);
	pos->img.exit_o = init_img(pos, "textures/exit_o.xpm", \
	&pos->img.exit_o_data);
	pos->img.player = init_img(pos, "textures/player.xpm", \
	&pos->img.player_data);
	pos->img.player_r = init_img(pos, "textures/player_r.xpm", \
	&pos->img.player_r_data);
	pos->img.empty_space = init_img(pos, "textures/background1.xpm", \
	&pos->img.empty_space_data);
	pos->img.enemy = init_img(pos, "textures/enemy.xpm", \
	&pos->img.enemy_data);
}

void	*init_img(t_map *pos, char *file_path, t_data *img_data)
{
	void	*image;

	pos->img_height = 0;
	pos->img_width = 0;
	image = mlx_xpm_file_to_image(pos->mlx, file_path, \
	&pos->img_width, &pos->img_height);
	if (!image)
	{
		ft_printf("Error while loading image\n");
		close_it(pos, 1);
	}
	img_data->img = image;
	img_data->addr = mlx_get_data_addr(image, &img_data->bits_per_pixel, \
					&img_data->line_length, &img_data->endian);
	return (image);
}

void	render_background(t_map *pos)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < pos->map_height)
	{
		x = 0;
		while (x < pos->map_width)
		{
			mlx_put_image_to_window(pos->mlx, pos->win, \
			pos->img.empty_space, x, y);
			x++;
		}
		y++;
	}
}

void	render_item(t_map *pos, int x, int y, char dir)
{
	if (dir == 'l' || dir == 'r')
		pos->last_dir = dir;
	handle_item(pos, x, y);
}

void	render_map(t_map *pos)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	render_background(pos);
	render_item(pos, x, y, 'r');
}
