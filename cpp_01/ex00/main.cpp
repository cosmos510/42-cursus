/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:05:14 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/06 11:12:16 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main()
{
	std::cout << "*** randomChump function ***" << std::endl;
	randomChump("random chump");

	std::cout << "*** newZombie function ***" << std::endl;
	Zombie* allocated_zombie = newZombie("allocated zombie");
	allocated_zombie->announce();
	delete allocated_zombie;

	return 0;
}