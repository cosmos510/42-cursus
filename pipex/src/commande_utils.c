/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:25:21 by cosmos            #+#    #+#             */
/*   Updated: 2025/01/11 17:32:05 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**create_args(char **temp, char **args, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		args[i] = ft_strdup(temp[i]);
		if (!args[i])
		{
			while (--i >= 0)
				free(args[i]);
			free(args);
			free_it(temp);
			return (NULL);
		}
		i++;
	}
	args[i] = NULL;
	free_it(temp);
	return (args);
}

char	**create_command_args(char *arg)
{
	char	**temp;
	char	**args;
	int		count;

	temp = ft_split(arg, ' ');
	count = 0;
	if (!temp)
		return (NULL);
	while (temp[count])
		count++;
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
	{
		free_it(temp);
		return (NULL);
	}
	return (create_args(temp, args, count));
}
