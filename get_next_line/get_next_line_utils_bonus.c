/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 07:45:18 by maximemarti       #+#    #+#             */
/*   Updated: 2024/10/21 13:13:00 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	safe_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

ssize_t	ft_strlen(char *s1)
{
	ssize_t	i;

	i = 0;
	while (s1[i])
		i++;
	return (i);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = (char *)malloc(sizeof(char) \
	* (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		new_str[i++] = s2[j++];
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new_str;

	if (!s1)
	{
		s1 = (char *)malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	new_str = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	return (new_str);
}
