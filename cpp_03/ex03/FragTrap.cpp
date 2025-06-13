/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:11:37 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 22:16:48 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap()
{
	this->hit = 100;
	this->energy = 100;
	this->attack_p = 30;
	std::cout << "FragTrap " << name << " was created with default constructor" << std::endl;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	this->hit = 100;
	this->energy = 100;
	this->attack_p = 30;
	std::cout << "FragTrap " << name << " was created with parameterized constructor" << std::endl;
}

FragTrap::FragTrap(const FragTrap& value) : ClapTrap(value)
{
	std::cout << "FragTrap " << name << " was created with copy constructor" << std::endl;
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap " << name << "'s Destructor called" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& value)
{
	if (this != &value)
	{
		this->name = value.name;
		this->hit = value.hit;
		this->energy = value.energy;
		this->attack_p = value.attack_p;
	}
	std::cout << "FragTrap copy assignment operator called for " << name << std::endl;
	return *this;
}

void FragTrap::attack(const std::string& target)
{
	if (energy > 0 && hit > 0)
	{
		std::cout << "FragTrap " << name << " attacks " << target << ", causing " << attack_p << " points of damage!" << std::endl;
		energy--;
		std::cout << "Energy left: " << energy << std::endl;
	}
	else
		std::cout << "FragTrap " << name << " can't attack" << std::endl;
}

void FragTrap::highFivesGuys(void)
{
	if (hit > 0)
		std::cout << "FragTrap " << name << " requests a high five!" << std::endl;
	else
		std::cout << "FragTrap " << name << " can't high five" << std::endl;
}