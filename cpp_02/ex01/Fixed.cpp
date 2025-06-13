/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:01:11 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 18:23:42 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>

// Constructeurs
Fixed::Fixed()
{
	value = 0;
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int n)
{
	std::cout << "Int constructor called" << std::endl;
	value = n << 8;
}

Fixed::Fixed(const float n)
{
	std::cout << "Float constructor called" << std::endl;
	this->value = roundf(n * (1 << nbr_bit));
}

Fixed::Fixed(const Fixed& other)
{
	std::cout << "Copy constructor called" << std::endl;
	this->value = other.getRawBits();
}

// Opérateur d’affectation
Fixed& Fixed::operator=(const Fixed& other)
{
	std::cout << "Copy assignment operator called" << std::endl;

	if (this != &other) {
		this->value = other.getRawBits();
	}
	return *this;
}

// Destructeur
Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

// Méthodes d’accès
int Fixed::getRawBits(void) const
{
	return this->value;
}

void Fixed::setRawBits(int const raw)
{
	this->value = raw;
}

float Fixed::toFloat(void) const
{
	return (float)value / (1 << nbr_bit);
}

int Fixed::toInt(void) const
{
	return value >> nbr_bit;
}

std::ostream& operator<<(std::ostream& os, const Fixed& fixed)
{
	os << fixed.toFloat();
	return os;
}