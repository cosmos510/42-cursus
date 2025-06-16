/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 09:17:09 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 18:24:41 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

// Déclaration de la classe Fixed
class Fixed
{
	private:
		// Attributs privés
		int value;
		static const int nbr_bit = 8;

	public:
		// Constructeurs et destructeur
		Fixed();
		Fixed(const Fixed& value);
		~Fixed();

		// Opérateur d’affectation
		Fixed& operator=(const Fixed&);

		// Méthodes d'accès
		int getRawBits(void) const;
		void setRawBits(int const raw);
};

#endif