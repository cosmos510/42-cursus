/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:08:44 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 18:36:10 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int main(void)
{
	Fixed a;
	Fixed const b(Fixed(5.05f) * Fixed(2));

	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << "a: " << a << std::endl;

	std::cout << "b: " << b << std::endl;

	std::cout << "b > a: " << (b > a) << std::endl;
	std::cout << "b == a: " << (b == a) << std::endl;
	std::cout << "b <= a: " << (b <= a) << std::endl;
	std::cout << "b / a: " << (b / a) << std::endl;

	std::cout << Fixed::max(a, b) << std::endl;
}