/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:53:59 by cosmos            #+#    #+#             */
/*   Updated: 2025/01/06 21:41:52 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	handle_player_move(t_map *pos, int new_x, int new_y, char render_direction)
{
	int	x;
	int	y;

	x = pos->p_x_start;
	y = pos->p_y_start;
	if (pos->map[new_y][new_x] != '1' && pos->map[new_y][new_x] != 'E' \
	&& pos->map[new_y][new_x] != 'S')
	{
		if (pos->map[new_y][new_x] == 'C')
			pos->col_game--;
		pos->map[new_y][new_x] = 'P';
		pos->map[y][x] = '0';
		render_item(pos, 0, 0, render_direction);
		pos->p_x_start = new_x;
		pos->p_y_start = new_y;
		pos->move_count++;
		ft_printf("Number of moves: %d\n", pos->move_count);
	}
	return (0);
}

int	render_die_bonus(t_map *pos)
{
	mlx_string_put(pos->mlx, pos->win, 50, 50, \
	0xFFFFFF, "You hit the wish you died  \
	Press escape to exit or the red cross");
	mlx_string_put(pos->mlx, pos->win, 50 + 1, 50, \
	0xFFFFFF, "You hit the wish you died   \
	Press escape to exit or the red cross");
	mlx_string_put(pos->mlx, pos->win, 50, 50 + 1, \
	0xFFFFFF, "You hit the wish you died   \
	Press escape to exit or the red cross");
	mlx_string_put(pos->mlx, pos->win, 50 + 1, 50 + 1, \
	0xFFFFFF, "You hit the wish you died   \
	Press escape to exit or the red cross");
	return (0);
}

int	render_final_bonus(t_map *pos)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_itoa(pos->move_count);
	pos->move_bonus = ft_strjoin("You finished the level in: ", tmp);
	mlx_string_put(pos->mlx, pos->win, 50, 50, 0xFFFFFF, pos->move_bonus);
	mlx_string_put(pos->mlx, pos->win, 50 + 1, 50, 0xFFFFFF, pos->move_bonus);
	mlx_string_put(pos->mlx, pos->win, 50, 50 + 1, 0xFFFFFF, pos->move_bonus);
	mlx_string_put(pos->mlx, pos->win, 50 + 1, 50 + 1, \
	0xFFFFFF, pos->move_bonus);
	mlx_string_put(pos->mlx, pos->win, 300, 50, 0xFFFFFF, \
	"Press escape to exit or the red cross");
	mlx_string_put(pos->mlx, pos->win, 300 + 1, 50, 0xFFFFFF, \
	"Press escape to exit or the red cross");
	mlx_string_put(pos->mlx, pos->win, 300, 50 + 1, 0xFFFFFF, \
	"Press escape to exit or the red cross");
	mlx_string_put(pos->mlx, pos->win, 300 + 1, 50 + 1, 0xFFFFFF, \
	"Press escape to exit or the red cross");
	free(tmp);
	free(pos->move_bonus);
	return (0);
}

int	check_game_conditions(t_map *pos, int new_x, int new_y)
{
	if (pos->map[new_y][new_x] == 'E' && pos->col_game == 0)
	{
		pos->move_count++;
		pos->map[new_y][new_x] = 'E';
		pos->map[pos->p_y_start][pos->p_x_start] = '0';
		render_item(pos, 0, 0, 'l');
		ft_printf("Number of moves: %d\n", pos->move_count);
		ft_printf("You finished the level!\n");
		ft_printf("Press escape to exit or the red cross\n");
		pos->game_active = 1;
		render_final_bonus(pos);
	}
	if (pos->map[new_y][new_x] == 'S')
	{
		pos->map[new_y][new_x] = 'S';
		pos->map[pos->p_y_start][pos->p_x_start] = '0';
		render_item(pos, 0, 0, 'l');
		ft_printf("You hit the wish you died\n");
		ft_printf("Press escape to exit or the red cross\n");
		pos->game_active = 1;
		render_die_bonus(pos);
	}
	if (pos->game_active == 0)
		render_move_bonus(pos);
	return (0);
}

int	move_in_direction(t_map *pos, char direction, int delta)
{
	int		x;
	int		y;
	int		new_x;
	int		new_y;
	char	render_direction;

	x = pos->p_x_start;
	y = pos->p_y_start;
	new_x = x;
	new_y = y;
	render_direction = 'n';
	if (direction == 'y')
		new_y = y + delta;
	else if (direction == 'x')
		new_x = x + delta;
	if (direction == 'x')
	{
		if (delta == -1)
			render_direction = 'l';
		else if (delta == 1)
			render_direction = 'r';
	}
	handle_player_move(pos, new_x, new_y, render_direction);
	check_game_conditions(pos, new_x, new_y);
	return (0);
}
