/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 12:00:00 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/16 12:00:01 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>

int main() {
	std::cout << "=== TEST 1: Char literals ===" << std::endl;
	ScalarConverter::convert("'a'");
	ScalarConverter::convert("'z'");
	ScalarConverter::convert("'0'");

	std::cout << "\n=== TEST 2: Int literals ===" << std::endl;
	ScalarConverter::convert("0");
	ScalarConverter::convert("42");
	ScalarConverter::convert("-42");
	ScalarConverter::convert("2147483647");
	ScalarConverter::convert("-2147483648");

	std::cout << "\n=== TEST 3: Float literals ===" << std::endl;
	ScalarConverter::convert("0.0f");
	ScalarConverter::convert("4.2f");
	ScalarConverter::convert("-4.2f");
	ScalarConverter::convert("42.0f");

	std::cout << "\n=== TEST 4: Double literals ===" << std::endl;
	ScalarConverter::convert("0.0");
	ScalarConverter::convert("4.2");
	ScalarConverter::convert("-4.2");
	ScalarConverter::convert("42.0");

	std::cout << "\n=== TEST 5: Special values ===" << std::endl;
	ScalarConverter::convert("nan");
	ScalarConverter::convert("nanf");
	ScalarConverter::convert("+inf");
	ScalarConverter::convert("-inf");
	ScalarConverter::convert("+inff");
	ScalarConverter::convert("-inff");

	std::cout << "\n=== TEST 6: Non-displayable chars ===" << std::endl;
	ScalarConverter::convert("0");
	ScalarConverter::convert("31");
	ScalarConverter::convert("127");

	std::cout << "\n=== TEST 7: Overflow cases ===" << std::endl;
	ScalarConverter::convert("999999999999");
	ScalarConverter::convert("-999999999999");

	std::cout << "\n=== TEST 8: Invalid inputs ===" << std::endl;
	ScalarConverter::convert("abc");
	ScalarConverter::convert("42.42.42");
	ScalarConverter::convert("");

	return 0;
}
