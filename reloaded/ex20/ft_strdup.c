/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:27:55 by maximemarti       #+#    #+#             */
/*   Updated: 2024/09/21 19:38:02 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	int		i;
	int		j;
	char	*dup;

	i = ft_strlen(src);
	j = 0;
	dup = malloc(sizeof(char) * i + 1);
	if (dup == NULL)
		return (NULL);
	while (src[j])
	{
		dup[j] = src[j];
		j++;
	}
	dup[j] = '\0';
	return (dup);
}
