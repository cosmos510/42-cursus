/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:39:36 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/11 11:05:33 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_delimiter(char c, const char *delimiters)
{
	while (*delimiters)
	{
		if (c == *delimiters)
			return (true);
		delimiters++;
	}
	return (false);
}

void	initialize_vars(int *j, int *s_word)
{
	*j = 0;
	*s_word = -1;
}

int	get_end(const char *s, size_t i, const char *delimiters)
{
	while (s[i] && !is_delimiter(s[i], delimiters))
		i++;
	return (i);
}

char	*create_word(const char *str, int start, int end)
{
	int		len;
	char	*word;
	int		i;

	len = end - start;
	if (!str)
		return (NULL);
	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = str[start + i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

void	free_array(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
