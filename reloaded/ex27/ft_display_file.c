/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 10:20:41 by maximemarti       #+#    #+#             */
/*   Updated: 2024/09/22 12:12:01 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_display_file.h"

int	ft_display_file(char *file)
{
	int		fd;
	int		sf;
	char	buf[1024];

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Cannot read file.\n", 18);
		return (-1);
	}
	while ((sf = read(fd, buf, 1024)) > 0)
		write(1, buf, sf);
	close(fd);
	return (0);
}

int	main(int ac, char *av[])
{
	if (ac == 1)
	{
		write(2, "File name missing.\n", 19);
		return (0);
	}
	if (ac > 2)
	{
		write(2, "Too many arguments.\n", 20);
		return (0);
	}
	else
		ft_display_file(av[1]);
	return (0);
}
