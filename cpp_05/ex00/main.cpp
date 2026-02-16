/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 12:00:00 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/16 17:50:45 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include <iostream>

int main() {
	std::cout << "=== TEST 1: Valid bureaucrat ===" << std::endl;
	try {
		Bureaucrat bob("Bob", 75);
		std::cout << bob << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 2: Grade too high (0) ===" << std::endl;
	try {
		Bureaucrat invalid("Invalid", 0);
		std::cout << invalid << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 3: Grade too low (151) ===" << std::endl;
	try {
		Bureaucrat invalid("Invalid", 151);
		std::cout << invalid << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 4: Increment grade ===" << std::endl;
	try {
		Bureaucrat alice("Alice", 2);
		std::cout << alice << std::endl;
		alice.incrementGrade();
		std::cout << alice << std::endl;
		alice.incrementGrade();
		std::cout << alice << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 5: Decrement grade ===" << std::endl;
	try {
		Bureaucrat charlie("Charlie", 149);
		std::cout << charlie << std::endl;
		charlie.decrementGrade();
		std::cout << charlie << std::endl;
		charlie.decrementGrade();
		std::cout << charlie << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 6: Copy constructor ===" << std::endl;
	{
		Bureaucrat original("Original", 50);
		Bureaucrat copy(original);
		std::cout << "Original: " << original << std::endl;
		std::cout << "Copy: " << copy << std::endl;
	}

	std::cout << "\n=== TEST 7: Assignment operator ===" << std::endl;
	{
		Bureaucrat a("A", 10);
		Bureaucrat b("B", 100);
		std::cout << "Before: " << a << " | " << b << std::endl;
		b = a;
		std::cout << "After: " << a << " | " << b << std::endl;
	}

	std::cout << "\n=== TEST 8: Boundary values ===" << std::endl;
	try {
		Bureaucrat highest("Highest", 1);
		Bureaucrat lowest("Lowest", 150);
		std::cout << highest << std::endl;
		std::cout << lowest << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
