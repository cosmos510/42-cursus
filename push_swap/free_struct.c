/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:00:41 by maximemarti       #+#    #+#             */
/*   Updated: 2024/12/19 01:05:50 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_stack(t_stack **lst)
{
	t_stack	*c;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		c = (*lst)->next;
		free(*lst);
		*lst = c;
	}
	*lst = NULL;
}

void	ft_free(char **to_free)
{
	int	i;

	i = 0;
	if (!to_free)
		return ;
	while (to_free[i])
		free(to_free[i++]);
	free(to_free);
	to_free = NULL;
}

void	free_and_exit(char **tmp_bis)
{
	if (tmp_bis)
		ft_free(tmp_bis);
	exit(1);
}
