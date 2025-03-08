/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:58:41 by cosmos            #+#    #+#             */
/*   Updated: 2025/01/08 21:47:14 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_images
{
	void	*background;
	t_data	background_data;
	void	*wall;
	t_data	wall_data;
	void	*coll;
	t_data	coll_data;
	void	*exit;
	t_data	exit_data;
	void	*exit_o;
	t_data	exit_o_data;
	void	*player;
	t_data	player_data;
	void	*player_r;
	t_data	player_r_data;
	void	*empty_space;
	t_data	empty_space_data;
	void	*enemy;
	t_data	enemy_data;
}	t_images;
typedef struct s_map
{
	int			collectibles;
	int			col_game;
	int			x_map_size;
	int			y_map_size;
	int			map_width;
	int			map_height;
	char		**map;
	int			exit_found;
	int			p_x_start;
	int			p_y_start;
	void		*mlx;
	void		*win;
	t_images	img;
	int			img_width;
	int			img_height;
	int			move_count;
	char		*move_bonus;
	char		last_dir;
	int			game_active;

}	t_map;

char	**read_map(char *av);
int		handle_args(int ac, char **av, char **map, t_map *pos);
int		check_opening_file(char *av);
int		check_file_fomar(char *file);
int		check_map(char **map, t_map *pos);
int		check_p(char **map);
int		check_e(char **map);
int		check_c(char **map, t_map *pos);
int		check_surrender_wall(char **map);
void	free_map(char **map);
int		is_map_solvable(char **map, t_map *pos);
int		find_x_start(char **map);
int		find_y_start(char **map);
int		explore_map(t_map *pos, int x_start, int y_start, char **map);
int		check_map_size(char **map, t_map *pos);
char	**dup_map(char **map, int y_map_size);
void	exit_clean(char **map);
void	load_img(t_map	*pos);
void	*init_img(t_map *pos, char *file_path, t_data *img_data);
void	init_struct2(t_map *pos);
void	render_map(t_map *pos);
void	render_background(t_map *pos);
void	render_item(t_map *pos, int x, int y, char dir);
int		close_it(t_map *pos, int exit);
void	destroy_mlx(t_map *pos);
int		move_it(int key_presed, t_map *pos);
int		move_right(t_map *pos);
int		move_left(t_map *pos);
int		move_down(t_map *pos);
int		move_up(t_map *pos);
int		render_move_bonus(t_map *pos);
void	handle_exit(t_map *pos, int x, int y);
void	handle_p(t_map *pos, int x, int y);
void	handle_item(t_map *pos, int x, int y);
int		handle_player_move(t_map *pos, int new_x, int new_y, \
		char render_direction);
int		check_game_conditions(t_map *pos, int new_x, int new_y);
int		move_in_direction(t_map *pos, char direction, int delta);
char	**split_the_map(char *av);
void	check_tmp_map(char *tmp_map, int fd);
int		render_final_bonus(t_map *pos);
int		render_die_bonus(t_map *pos);
#endif