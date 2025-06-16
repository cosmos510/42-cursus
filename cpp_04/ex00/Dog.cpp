/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 23:22:18 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 23:26:39 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() : Animal()
{
	type = "Dog";
	std::cout << "Dog was created with default constructor" << std::endl;
}

Dog::Dog(const Dog& value) : Animal(value)
{
	this->type = value.type;
	std::cout << "Dog was created with copy constructor type: "  << type << std::endl;
}

Dog::~Dog()
{
	std::cout << "Dog's Destructor called" << std::endl;
}

Dog& Dog::operator=(const Dog& value)
{
	if (this != &value)
	{
		Animal::operator=(value);
	}
	std::cout << "Dog copy assignment operator called for Dog type : " << type << std::endl;
	return *this;
}

void Dog::makeSound() const
{
	std::cout << "Wouaf" << std::endl;
}
