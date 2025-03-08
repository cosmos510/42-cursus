/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:15:47 by cosmos            #+#    #+#             */
/*   Updated: 2025/01/13 23:03:29 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **env)
{
	int	here_doc_mod;

	here_doc_mod = 0;
	if (ac < 5)
	{
		ft_putstr_fd("Error, bad argument\n", 2);
		ft_putstr_fd("Usage: ./pipex filein cmd1 cmd2 fileout\n", 2);
		exit(1);
	}
	else
	{
		if (ft_strncmp(av[1], "here_doc", 9) == 0)
			here_doc_mod = 1;
		if (here_doc_mod == 1 && ac != 6)
		{
			ft_putstr_fd("Error, bad argument\n", 2);
			ft_putstr_fd("Usage: ./pipex here_doc LIMITER cmd cmd1 file\n", 2);
			exit(1);
		}
		handle_pipes_bonus(ac, av, env, here_doc_mod);
	}
	return (0);
}
