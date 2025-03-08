/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 09:45:24 by cosmos            #+#    #+#             */
/*   Updated: 2025/01/26 16:18:57 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_it(char **s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i] && s)
		{
			free(s[i]);
			i++;
		}
		free(s);
	}
}

void	error(void)
{
	exit(EXIT_FAILURE);
}

void	error2(char **path_env, char **args)
{
	ft_putstr_fd("Commande not found\n", 2);
	free_it(path_env);
	free(args);
	exit(127);
}

void	clean_up(char **path_env, char **args, char *path)
{
	if (path_env)
		free_it(path_env);
	if (args)
	{
		free(args[1]);
		free(args);
	}
	if (path)
		free(path);
}

void	close_it(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	error();
}
