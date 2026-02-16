/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 08:28:58 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/16 08:28:59 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include <iostream>

int main() {
	std::cout << "=== Test 1: Valid bureaucrat creation ===" << std::endl;
	try {
		Bureaucrat bob("Bob", 75);
		std::cout << bob << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 2: Grade too high (0) ===" << std::endl;
	try {
		Bureaucrat invalid("Invalid", 0);
		std::cout << invalid << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 3: Grade too low (151) ===" << std::endl;
	try {
		Bureaucrat invalid("Invalid", 151);
		std::cout << invalid << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 4: Increment grade ===" << std::endl;
	try {
		Bureaucrat alice("Alice", 3);
		std::cout << alice << std::endl;
		alice.incrementGrade();
		std::cout << alice << std::endl;
		alice.incrementGrade();
		std::cout << alice << std::endl;
		alice.incrementGrade();
		std::cout << alice << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 5: Decrement grade ===" << std::endl;
	try {
		Bureaucrat charlie("Charlie", 148);
		std::cout << charlie << std::endl;
		charlie.decrementGrade();
		std::cout << charlie << std::endl;
		charlie.decrementGrade();
		std::cout << charlie << std::endl;
		charlie.decrementGrade();
		std::cout << charlie << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 6: Edge cases (1 and 150) ===" << std::endl;
	try {
		Bureaucrat top("Top", 1);
		Bureaucrat bottom("Bottom", 150);
		std::cout << top << std::endl;
		std::cout << bottom << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
