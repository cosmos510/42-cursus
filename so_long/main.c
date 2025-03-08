/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:43:20 by cosmos            #+#    #+#             */
/*   Updated: 2025/01/02 22:30:02 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

int	main(int ac, char **av)
{
	char		**map;
	t_map		pos;
	t_images	image;

	ft_bzero(&pos, sizeof(t_map));
	ft_bzero(&image, sizeof(t_images));
	map = NULL;
	if (handle_args(ac, av, map, &pos) == -1)
		return (-1);
	init_struct2(&pos);
	render_map(&pos);
	mlx_hook(pos.win, 2, 1L << 0, move_it, &pos);
	mlx_hook(pos.win, 17, 0L, close_it, &pos);
	mlx_loop(pos.mlx);
	return (0);
}
