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

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main() {
	std::cout << "=== TEST 1: Valid form creation ===" << std::endl;
	try {
		Form form("Tax Form", 50, 25);
		std::cout << form << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 2: Form grade too high ===" << std::endl;
	try {
		Form invalid("Invalid", 0, 50);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 3: Form grade too low ===" << std::endl;
	try {
		Form invalid("Invalid", 50, 151);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 4: Successful signing ===" << std::endl;
	try {
		Bureaucrat bob("Bob", 30);
		Form form("Contract", 50, 25);
		std::cout << form << std::endl;
		bob.signForm(form);
		std::cout << form << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 5: Failed signing (grade too low) ===" << std::endl;
	try {
		Bureaucrat intern("Intern", 100);
		Form form("Top Secret", 50, 25);
		std::cout << form << std::endl;
		intern.signForm(form);
		std::cout << form << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 6: Sign already signed form ===" << std::endl;
	try {
		Bureaucrat alice("Alice", 1);
		Form form("Document", 50, 25);
		alice.signForm(form);
		alice.signForm(form);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 7: Copy constructor ===" << std::endl;
	{
		Form original("Original", 50, 25);
		Form copy(original);
		std::cout << "Original: " << original << std::endl;
		std::cout << "Copy: " << copy << std::endl;
	}

	std::cout << "\n=== TEST 8: Boundary values ===" << std::endl;
	try {
		Form highest("Highest", 1, 1);
		Form lowest("Lowest", 150, 150);
		std::cout << highest << std::endl;
		std::cout << lowest << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
