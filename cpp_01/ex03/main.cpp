/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:10:10 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/06 17:16:51 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"
#include "HumanA.hpp"
#include "HumanB.hpp"

int main()
{
	
	Weapon club = Weapon("crude spiked club");
	HumanA bob("Bob", club);
	bob.attack();
	club.setType("some other type of club");
	bob.attack();


	Weapon club2 = Weapon("");
	HumanB jim("Jim");
	jim.setWeapon(club2);
	jim.attack();
	club2.setType("some other type of club");
	jim.attack();
	
	return 0;
}