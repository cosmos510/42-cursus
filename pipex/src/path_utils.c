/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:10:29 by cosmos            #+#    #+#             */
/*   Updated: 2025/01/12 17:21:14 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**find_path_env(char **env)
{
	char	*path_str;
	char	**path_split;

	path_str = get_path_string(env);
	if (!path_str)
		return (NULL);
	path_split = process_path_string(path_str);
	if (!path_split)
		return (NULL);
	return (path_split);
}

char	*get_path_string(char **env)
{
	int	i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (ft_strdup(env[i] + 5));
		i++;
	}
	return (NULL);
}

char	**process_path_string(char *path_str)
{
	char	**path_split;

	if (!path_str)
		return (NULL);
	path_split = ft_split(path_str, ':');
	free(path_str);
	if (!path_split)
		return (NULL);
	if (!add_slash(path_split))
		return (NULL);
	return (path_split);
}

char	**add_slash(char **path)
{
	int		i;
	char	*temp;

	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		if (!temp)
		{
			free_it(path);
			return (NULL);
		}
		free(path[i]);
		path[i] = temp;
		i++;
	}
	return (path);
}

char	*find_path(char **path, char *arg)
{
	char	*commande;
	int		i;

	if (!path || !arg)
		return (NULL);
	i = 0;
	while (path[i])
	{
		commande = ft_strjoin(path[i], arg);
		if (!commande)
			return (NULL);
		if (access(commande, F_OK) == 0)
			return (commande);
		free(commande);
		i++;
	}
	free(arg);
	return (NULL);
}
