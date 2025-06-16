/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:00:59 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 18:23:00 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed
{
private:
	int value;
	static const int nbr_bit = 8;

public:
	Fixed();
	Fixed(const int n);
	Fixed(const float n);
	Fixed(const Fixed& other);

	// Opérateur d’affectation
	Fixed& operator=(const Fixed&);

	// Destructeur
	~Fixed();

	// Méthodes d’accès
	int getRawBits(void) const;
	void setRawBits(int const raw);

	// Méthodes de conversion
	float toFloat(void) const;
	int toInt(void) const;
};

// Surcharge d'opérateur pour l'affichage
std::ostream& operator<<(std::ostream& os, const Fixed& fixed);

#endif