/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 18:20:52 by cosmos            #+#    #+#             */
/*   Updated: 2025/01/02 22:31:43 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_struct2(t_map *pos)
{
	pos->mlx = mlx_init();
	if (!pos->mlx)
	{
		ft_printf("Error initializing mlx\n");
		exit(1);
	}
	load_img(pos);
	pos->map_height = pos->img_height * (pos->y_map_size + 1);
	pos->map_width = pos->img_width * (pos->x_map_size + 1);
	pos->win = mlx_new_window(pos->mlx, pos->map_width, \
	pos->map_height, "so_long");
	if (!pos->win)
	{
		ft_printf("Error creating window\n");
		exit(1);
	}
}
