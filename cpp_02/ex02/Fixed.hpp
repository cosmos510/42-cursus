/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:07:57 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 18:26:28 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed
{
	private:
		int value;
		static const int nbr_bit = 8;

	public:
		// Constructeurs / Destructeur
		Fixed();
		Fixed(const int n);
		Fixed(const float n);
		Fixed(const Fixed& other);
		Fixed& operator=(const Fixed& other);
		~Fixed();

		// Accesseurs
		int getRawBits(void) const;
		void setRawBits(int const raw);
		float toFloat(void) const;
		int toInt(void) const;

		// Opérateurs de comparaison
		bool operator>(const Fixed& other) const;
		bool operator<(const Fixed& other) const;
		bool operator>=(const Fixed& other) const;
		bool operator<=(const Fixed& other) const;
		bool operator==(const Fixed& other) const;
		bool operator!=(const Fixed& other) const;

		// Opérateurs arithmétiques
		Fixed operator+(const Fixed& other) const;
		Fixed operator-(const Fixed& other) const;
		Fixed operator*(const Fixed& other) const;
		Fixed operator/(const Fixed& other) const;

		// Opérateurs d'incrémentation/décrémentation
		Fixed& operator++();     // pré-incrémentation
		Fixed operator++(int);   // post-incrémentation
		Fixed& operator--();     // pré-décrémentation
		Fixed operator--(int);   // post-décrémentation

		// Fonctions min/max
		static Fixed& min(Fixed& a, Fixed& b);
		static const Fixed& min(const Fixed& a, const Fixed& b);
		static Fixed& max(Fixed& a, Fixed& b);
		static const Fixed& max(const Fixed& a, const Fixed& b);
};

// Opérateur d'affichage
std::ostream& operator<<(std::ostream& os, const Fixed& fixed);

#endif