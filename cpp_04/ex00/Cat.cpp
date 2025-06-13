/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 23:28:00 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 23:31:19 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : Animal()
{
	type = "Cat";
	std::cout << "Cat was created with default constructor" << std::endl;
}

Cat::Cat(const Cat& value) : Animal(value)
{
	std::cout << "Cat was created with copy constructor type: "  << type << std::endl;
}

Cat::~Cat()
{
	std::cout << "Cat's Destructor called" << std::endl;
}

Cat& Cat::operator=(const Cat& value)
{
	if (this != &value)
	{
		Animal::operator=(value);
	}
	std::cout << "Cat copy assignment operator called for Cat type : " << type << std::endl;
	return *this;
}

void Cat::makeSound() const
{
	std::cout << "miaou" << std::endl;
}
