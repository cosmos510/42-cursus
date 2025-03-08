/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:57:50 by cosmos            #+#    #+#             */
/*   Updated: 2025/01/13 21:04:06 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **env)
{
	if (ac != 5)
	{
		ft_putstr_fd("Error, bad argument\n", 2);
		ft_putstr_fd("Usage: ./pipex filein cmd1 cmd2 fileout\n", 2);
		exit(1);
	}
	else
		handle_pipes(ac, av, env);
	return (0);
}
