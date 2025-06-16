/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongWrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 23:36:48 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 23:36:50 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat() : WrongAnimal()
{
	type = "WrongCat";
	std::cout << "WrongCat was created with default constructor" << std::endl;
}

WrongCat::WrongCat(const WrongCat& value) : WrongAnimal(value)
{
	std::cout << "WrongCat was created with copy constructor type: "  << type << std::endl;
}

WrongCat::~WrongCat()
{
	std::cout << "WrongCat's Destructor called" << std::endl;
}

WrongCat& WrongCat::operator=(const WrongCat& value)
{
	if (this != &value)
	{
		WrongAnimal::operator=(value);
	}
	std::cout << "WrongCat copy assignment operator called for WrongCat type : " << type << std::endl;
	return *this;
}

void WrongCat::makeSound() const
{
	std::cout << "uoaiam" << std::endl;
}