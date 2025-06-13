/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:49:49 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 19:26:57 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"


ClapTrap::ClapTrap()
{
	this->hit = 10;
	this->energy = 10;
	this->attack_p = 0;
	std::cout << "ClapTrap " << name << " was created with default constructor" << std::endl;
}

ClapTrap::ClapTrap(std::string name)
{
	this->name = name;
	this->hit = 10;
	this->energy = 10;
	this->attack_p = 0;
	std::cout << "ClapTrap " << name << " was created with parameterized constructor" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& value)
{
	this->name = value.name;
	this->hit = value.hit;
	this->energy = value.energy;
	this->attack_p = value.attack_p;
	std::cout << "ClapTrap " << name << " was created with copy constructor" << std::endl;
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap " << name << "'s Destructor called" << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& value)
{
	if (this != &value)
	{
		this->name = value.name;
		this->hit = value.hit;
		this->energy = value.energy;
		this->attack_p = value.attack_p;
	}
	std::cout << "ClapTrap copy assignment operator called for " << name << std::endl;
	return *this;
}

void ClapTrap::attack(const std::string& target)
{
	if (energy > 0 && hit > 0)
	{
		std::cout << "ClapTrap " << name << " attacks " << target << ", causing " << attack_p << " points of damage!" << std::endl;
		energy--;
		std::cout << "Energy left: " << energy << std::endl;
	}
	else
		std::cout << "ClapTrap " << name << " can't attack" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	std::cout << "ClapTrap " << name << " takes " << amount << " damage!" << std::endl;
	hit -= amount;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (energy > 0 && hit > 0)
	{
		std::cout << "ClapTrap " << name << " repairs itself, regaining " << amount << " hit points!" << std::endl;
		hit += amount;
		energy--;
	}
	else
		std::cout << "ClapTrap " << name << " can't repair" << std::endl;
}