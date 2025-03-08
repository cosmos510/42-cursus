/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 18:00:00 by cosmos            #+#    #+#             */
/*   Updated: 2025/01/08 21:47:25 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_opening_file(char *av)
{
	int	fd;

	fd = open(av, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error while opening the file\n");
		exit (1);
	}
	return (fd);
}

int	check_file_format(char *file)
{
	const char	*ext;

	if (ft_strrchr(file, '.') == NULL)
	{
		ft_printf("Wrong format file\nRequire .ber file\n");
		exit(1);
	}
	ext = ft_strrchr(file, '.');
	if (ft_strncmp(ext, ".ber", 4))
	{
		ft_printf("Wrong format file\nRequire .ber file\n");
		exit(1);
	}
	return (0);
}

char	**read_map(char *av)
{
	char	*tmp_map;
	char	*line;
	char	**map;
	int		fd;

	tmp_map = "";
	check_file_format(av);
	fd = check_opening_file(av);
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	tmp_map = ft_strjoin(tmp_map, line);
	free(line);
	while (line)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		tmp_map = ft_strjoin_free(tmp_map, line);
		free(line);
	}
	free(line);
	check_tmp_map(tmp_map, fd);
	map = split_the_map(tmp_map);
	return (map);
}

char	**dup_map(char **map, int y_map_size)
{
	int		i;
	char	**new_map;

	new_map = (char **)malloc(sizeof(char *) * (y_map_size + 2));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i <= y_map_size)
	{
		new_map[i] = ft_strdup(map[i]);
		if (!new_map[i])
			return (NULL);
		i++;
	}
	new_map[y_map_size + 1] = NULL;
	return (new_map);
}

int	handle_args(int ac, char **av, char **map, t_map *pos)
{
	if (ac != 2)
	{
		ft_printf("Please enter valid number of argument\n");
		ft_printf("Usage ./so_long map.ber\n");
		return (-1);
	}
	map = read_map(av[1]);
	if (!map)
	{
		ft_printf("Error while reading the map\n");
		close_it(pos, 1);
	}
	pos->map = map;
	if (!check_map(map, pos) || is_map_solvable(map, pos) != 0)
	{
		exit_clean(map);
		exit(1);
	}
	return (0);
}
