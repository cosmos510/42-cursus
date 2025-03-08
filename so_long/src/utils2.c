/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 23:32:11 by cosmos            #+#    #+#             */
/*   Updated: 2025/01/08 21:47:40 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	check_tmp_map(char *tmp_map, int fd)
{
	int	i;

	i = 0;
	close(fd);
	while (tmp_map[i])
	{
		if (tmp_map[i] == '\n' && tmp_map[i + 1] == '\n')
		{
			free(tmp_map);
			exit(1);
		}
		i++;
	}
}

char	**split_the_map(char *tmp_map)
{
	char	**map;

	map = ft_split(tmp_map, '\n');
	free(tmp_map);
	return (map);
}
