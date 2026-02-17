/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 09:09:51 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/17 16:53:01 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "whatever.hpp"
#include <iostream>
#include <string>

int main() {
	std::cout << "=== TEST 1: Int swap ===" << std::endl;
	{
		int a = 2;
		int b = 3;
		std::cout << "Before: a = " << a << ", b = " << b << std::endl;
		::swap(a, b);
		std::cout << "After: a = " << a << ", b = " << b << std::endl;
	}

	std::cout << "\n=== TEST 2: Int min/max ===" << std::endl;
	{
		int a = 2;
		int b = 3;
		std::cout << "min(" << a << ", " << b << ") = " << ::min(a, b) << std::endl;
		std::cout << "max(" << a << ", " << b << ") = " << ::max(a, b) << std::endl;
	}

	std::cout << "\n=== TEST 3: String swap ===" << std::endl;
	{
		std::string a = "chaine1";
		std::string b = "chaine2";
		std::cout << "Before: a = " << a << ", b = " << b << std::endl;
		::swap(a, b);
		std::cout << "After: a = " << a << ", b = " << b << std::endl;
	}

	std::cout << "\n=== TEST 4: String min/max ===" << std::endl;
	{
		std::string a = "chaine1";
		std::string b = "chaine2";
		std::cout << "min = " << ::min(a, b) << std::endl;
		std::cout << "max = " << ::max(a, b) << std::endl;
	}

	std::cout << "\n=== TEST 5: Float ===" << std::endl;
	{
		float a = 3.14f;
		float b = 2.71f;
		std::cout << "Before: a = " << a << ", b = " << b << std::endl;
		::swap(a, b);
		std::cout << "After: a = " << a << ", b = " << b << std::endl;
		std::cout << "min = " << ::min(a, b) << std::endl;
		std::cout << "max = " << ::max(a, b) << std::endl;
	}

	std::cout << "\n=== TEST 6: Equal values ===" << std::endl;
	{
		int a = 42;
		int b = 42;
		std::cout << "min(" << a << ", " << b << ") = " << ::min(a, b) << std::endl;
		std::cout << "max(" << a << ", " << b << ") = " << ::max(a, b) << std::endl;
	}

	std::cout << "\n=== TEST 7: Negative numbers ===" << std::endl;
	{
		std::string c = "chaine1";
		std::string d = "chaine2";
		::swap(c, d);
		std::cout << "c = " << c << ", d = " << d << std::endl;
		std::cout << "min(" << c << ", " << d << ") = " << ::min(c, d) << std::endl;
		std::cout << "max(" << c << ", " << d << ") = " << ::max(c, d) << std::endl;
	}

	return 0;
}
/*int main( void ) {
int a = 2;
int b = 3;
::swap( a, b );
std::cout << "a = " << a << ", b = " << b << std::endl;
std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;
std::string c = "chaine1";
std::string d = "chaine2";
::swap(c, d);
std::cout << "c = " << c << ", d = " << d << std::endl;
std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;
return 0;
}*/