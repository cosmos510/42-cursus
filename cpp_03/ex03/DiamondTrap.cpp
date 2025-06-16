/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:34:37 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 22:53:57 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : FragTrap(), ScavTrap()
{
    hit = FragTrap::hit;
    energy = ScavTrap::energy;
    attack_p = FragTrap::attack_p;
	std::cout << "DiamondTrap " << name << " was created with default constructor" << std::endl;
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name"), FragTrap(name), ScavTrap(name)
{
	this->name = name;
    hit = FragTrap::hit;
    energy = ScavTrap::energy;
    attack_p = FragTrap::attack_p;
	std::cout << "DiamondTrap " << name << " was created with parameterized constructor" << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap& value) : ClapTrap(value), FragTrap(value), ScavTrap(value), name(value.name)
{
	std::cout << "DiamondTrap " << name << " was created with copy constructor" << std::endl;
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamondTrap " << name << "'s Destructor called" << std::endl;
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& value)
{
	if (this != &value)
	{
		this->name = value.name;
		ClapTrap::operator=(value);
	}
	std::cout << "DiamondTrap copy assignment operator called for " << name << std::endl;
	return *this;
}

void DiamondTrap::attack(const std::string& target)
{
	ScavTrap::attack(target);
}

void DiamondTrap::whoAmI()
{
	std::cout << "DiamondTrap name: " << name << std::endl;
	std::cout << "ClapTrap name: " << ClapTrap::name << std::endl;
}
