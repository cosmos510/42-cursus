/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:08:19 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/16 12:13:30 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>
#include <cmath>

// Constructeurs
Fixed::Fixed()
{
	value = 0;
}

Fixed::Fixed(const int n)
{
	value = n << nbr_bit;
}

Fixed::Fixed(const float n)
{
	value = roundf(n * (1 << nbr_bit));
}

Fixed::Fixed(const Fixed& other)
{
	value = other.getRawBits();
}

Fixed& Fixed::operator=(const Fixed& other)
{
	if (this != &other)
		value = other.getRawBits();
	return *this;
}

Fixed::~Fixed()
{
}

// Accesseurs
int Fixed::getRawBits(void) const
{
	return value;
}

void Fixed::setRawBits(int const raw)
{
	value = raw;
}

float Fixed::toFloat(void) const
{
	return (float)value / (1 << nbr_bit);
}

int Fixed::toInt(void) const
{
	return value >> nbr_bit;
}

// Opérateur <<
std::ostream& operator<<(std::ostream& os, const Fixed& fixed)
{
	os << fixed.toFloat();
	return os;
}

// Comparaison
bool Fixed::operator>(const Fixed& other) const { return value > other.value; }
bool Fixed::operator<(const Fixed& other) const { return value < other.value; }
bool Fixed::operator>=(const Fixed& other) const { return value >= other.value; }
bool Fixed::operator<=(const Fixed& other) const { return value <= other.value; }
bool Fixed::operator==(const Fixed& other) const { return value == other.value; }
bool Fixed::operator!=(const Fixed& other) const { return value != other.value; }

// Arithmétique
Fixed Fixed::operator+(const Fixed& other) const
{
	return Fixed(this->toFloat() + other.toFloat());
}

Fixed Fixed::operator-(const Fixed& other) const
{
	return Fixed(this->toFloat() - other.toFloat());
}

Fixed Fixed::operator*(const Fixed& other) const
{
	return Fixed(this->toFloat() * other.toFloat());
}

Fixed Fixed::operator/(const Fixed& other) const
{
	return Fixed(this->toFloat() / other.toFloat());
}

// Incrémentation / Décrémentation
Fixed& Fixed::operator++()
{
	value++;
	return *this;
}

Fixed Fixed::operator++(int)
{
	Fixed temp = *this;
	value++;
	return temp;
}

Fixed& Fixed::operator--()
{
	value--;
	return *this;
}

Fixed Fixed::operator--(int)
{
	Fixed temp = *this;
	value--;
	return temp;
}

// Min / Max
Fixed& Fixed::min(Fixed& a, Fixed& b)
{
	if (a < b)
		return a;
	else
		return b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b)
{
	if (a < b)
		return a;
	else
		return b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b)
{
	if (a > b)
		return a;
	else
		return b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b)
{
	if (a > b)
		return a;
	else
		return b;
}