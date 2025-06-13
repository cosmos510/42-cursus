/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongWrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 23:35:14 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 23:35:16 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal()
{
	std::cout << "WrongAnimal was created with default constructor" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& value)
{
	this->type = value.type;
	std::cout << "WrongAnimal was created with copy constructor type: "  << type << std::endl;
}

WrongAnimal::~WrongAnimal()
{
	std::cout << "WrongAnimal's Destructor called" << std::endl;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& value)
{
	if (this != &value)
	{
		this->type = value.type;
	}
	std::cout << "WrongAnimal copy assignment operator called for WrongAnimal type : " << type << std::endl;
	return *this;
}

void WrongAnimal::makeSound() const
{
	std::cout << "WrongAnimal has no sound yet" << std::endl;
}

std::string WrongAnimal::getType() const
{
	return type;
}