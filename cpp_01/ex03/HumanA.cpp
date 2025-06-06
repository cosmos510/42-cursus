/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:46:50 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/06 17:25:39 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"
#include "Weapon.hpp"

HumanA::HumanA(std::string name, Weapon& weapon)
	: _name(name), _Weapon(weapon)
{
}

void HumanA::attack()
{
	std::cout << _name << " attacks with their " << _Weapon.getType() << std::endl;
}