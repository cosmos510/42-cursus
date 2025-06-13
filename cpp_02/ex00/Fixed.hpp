/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 09:17:09 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 09:26:53 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

class Fixed
{
	private:
		int value;
		static const int nbr_bit;
	public:
		Fixed();
		Fixed(const Fixed& value);
		Fixed& operator=(const Fixed&); 
		~Fixed();
		int getRawBits(void) const;
		void setRawBits( int const raw );
};


#endif