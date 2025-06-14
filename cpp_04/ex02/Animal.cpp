/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 23:05:03 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 23:52:54 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal()
{
	std::cout << "Animal was created with default constructor" << std::endl;
}

Animal::Animal(const Animal& value)
{
	this->type = value.type;
	std::cout << "Animal was created with copy constructor type: "  << type << std::endl;
}

Animal::~Animal()
{
	std::cout << "Animal's Destructor called" << std::endl;
}

Animal& Animal::operator=(const Animal& value)
{
	if (this != &value)
	{
		this->type = value.type;
	}
	std::cout << "Animal copy assignment operator called for animal type : " << type << std::endl;
	return *this;
}

void Animal::makeSound() const
{
	std::cout << "Animal has no sound yet" << std::endl;
}

std::string Animal::getType() const
{
	return type;
}