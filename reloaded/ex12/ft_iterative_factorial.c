/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:57:05 by maximemarti       #+#    #+#             */
/*   Updated: 2024/09/21 18:06:38 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_factorial(int nb)
{
	int	result;

	result = nb;
	if (nb < 0)
		return (0);
	if (nb == 0 || nb == 1)
		return (1);
	while (nb - 1 > 0)
	{
		if (result > 2147483647 / (nb - 1) || result < -2147483648 / (nb - 1))
			return (0);
		result *= nb -1;
		nb--;
	}
	return (result);
}
