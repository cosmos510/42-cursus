/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 21:46:25 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 22:40:42 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap()
{
	this->hit = 100;
	this->energy = 50;
	this->attack_p = 20;
	std::cout << "ScavTrap " << name << " was created with default constructor" << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	this->hit = 100;
	this->energy = 50;
	this->attack_p = 20;
	std::cout << "ScavTrap " << name << " was created with parameterized constructor" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& value) : ClapTrap(value)
{
	std::cout << "ScavTrap " << name << " was created with copy constructor" << std::endl;
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap " << name << "'s Destructor called" << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& value)
{
	if (this != &value)
	{
		this->name = value.name;
		this->hit = value.hit;
		this->energy = value.energy;
		this->attack_p = value.attack_p;
	}
	std::cout << "ScavTrap copy assignment operator called for " << name << std::endl;
	return *this;
}

void ScavTrap::attack(const std::string& target)
{
	if (energy > 0 && hit > 0)
	{
		std::cout << "ScavTrap " << name << " attacks " << target << ", causing " << attack_p << " points of damage!" << std::endl;
		energy--;
		std::cout << "Energy left: " << energy << std::endl;
	}
	else
		std::cout << "ScavTrap " << name << " can't attack" << std::endl;
}

void ScavTrap::guardGate()
{
	if (hit > 0)
		std::cout << "ScavTrap " << name << " is now in Gate keeper mode" << std::endl;
	else
		std::cout << "ScavTrap " << name << " can't guard the Gate" << std::endl;
}