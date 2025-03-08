/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:41:29 by cosmos            #+#    #+#             */
/*   Updated: 2025/01/06 12:10:19 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	move_it(int key_presed, t_map *pos)
{
	if (key_presed == 65307)
		close_it(pos, 0);
	if (pos->game_active == 1)
		return (0);
	if (key_presed == 100 || key_presed == 65363)
		move_right(pos);
	if (key_presed == 97 || key_presed == 65361)
		move_left(pos);
	if (key_presed == 115 || key_presed == 65364)
		move_down(pos);
	if (key_presed == 119 || key_presed == 65362)
		move_up(pos);
	return (0);
}

int	move_down(t_map *pos)
{
	return (move_in_direction(pos, 'y', 1));
}

int	move_up(t_map *pos)
{
	return (move_in_direction(pos, 'y', -1));
}

int	move_left(t_map *pos)
{
	return (move_in_direction(pos, 'x', -1));
}

int	move_right(t_map *pos)
{
	return (move_in_direction(pos, 'x', 1));
}
