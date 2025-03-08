/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmarti <maxmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:39:56 by maxmarti          #+#    #+#             */
/*   Updated: 2024/12/19 08:33:36 by maxmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_stack *st)
{
	t_stack	*s;

	s = st;
	while (s->next)
	{
		if (s->n > s->next->n)
			return (0);
		s = s->next;
	}
	return (1);
}

static void	push_swap(t_stack **sa, t_stack **sb, int size)
{
	if (size == 2 && !is_sorted(*sa))
		swap_move(sa, NULL, "sa");
	else if (size == 3)
		small_sort(sa);
	else if (size > 3 && !is_sorted(*sa))
		big_sort(sa, sb);
}

int	main(int ac, char **av)
{
	int		size;
	t_stack	*sa;
	t_stack	*sb;

	if (ac < 2)
		return (-1);
	check_args(ac, av);
	sa = create_stack(ac, av);
	sb = NULL;
	size = get_stack_size(sa);
	get_main_index(sa, size);
	push_swap(&sa, &sb, size);
	free_stack(&sa);
	free_stack(&sb);
	return (0);
}
