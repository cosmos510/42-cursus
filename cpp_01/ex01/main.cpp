/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:40:15 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/06 11:43:51 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main()
{
	int horde_size = 2;
	Zombie *horde = zombieHorde(horde_size, "zombie horde");
	for (int i = 0; i < horde_size; i++)
		horde[i].announce();
	delete[] horde;
	return 0;
}