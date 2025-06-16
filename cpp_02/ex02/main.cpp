/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:08:44 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/16 11:43:58 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int main(void)
{
	Fixed a;
	Fixed const b(Fixed(5.05f) * Fixed(2));

	std::cout << "Initial values:" << std::endl;
	std::cout << "a: " << a << std::endl;
	std::cout << "b: " << b << std::endl;

	std::cout << "\nIncrement tests:" << std::endl;
	std::cout << "++a: " << ++a << std::endl;
	std::cout << "a: " << a << std::endl;
	std::cout << "a++: " << a++ << std::endl;
	std::cout << "a (after a++): " << a << std::endl;

	std::cout << "\nComparison tests:" << std::endl;
	std::cout << "b > a: " << (b > a) << std::endl;
	std::cout << "b == a: " << (b == a) << std::endl;
	std::cout << "b <= a: " << (b <= a) << std::endl;

	std::cout << "\nArithmetic tests:" << std::endl;
	std::cout << "b + a: " << (b + a) << std::endl;
	std::cout << "b - a: " << (b - a) << std::endl;
	std::cout << "b * a: " << (b * a) << std::endl;
	if (a.toFloat() != 0.0f)
		std::cout << "b / a: " << (b / a) << std::endl;
	else
		std::cout << "b / a: Division by zero!" << std::endl;

	std::cout << "\nMax test:" << std::endl;
	std::cout << "max(a, b): " << Fixed::max(a, b) << std::endl;

	return 0;
}