/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 08:28:37 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/16 08:28:38 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main() {
	std::cout << "=== Test 1: Valid form creation ===" << std::endl;
	try {
		Form form1("Tax Form", 50, 25);
		std::cout << form1 << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 2: Form grade too high ===" << std::endl;
	try {
		Form form2("Invalid Form", 0, 50);
		std::cout << form2 << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 3: Form grade too low ===" << std::endl;
	try {
		Form form3("Invalid Form", 50, 151);
		std::cout << form3 << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 4: Successful signing ===" << std::endl;
	try {
		Bureaucrat bob("Bob", 30);
		Form form4("Contract", 50, 25);
		std::cout << bob << std::endl;
		std::cout << form4 << std::endl;
		bob.signForm(form4);
		std::cout << form4 << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 5: Failed signing (grade too low) ===" << std::endl;
	try {
		Bureaucrat alice("Alice", 100);
		Form form5("Important Document", 50, 25);
		std::cout << alice << std::endl;
		std::cout << form5 << std::endl;
		alice.signForm(form5);
		std::cout << form5 << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 6: Edge case (grade 1 bureaucrat) ===" << std::endl;
	try {
		Bureaucrat boss("Boss", 1);
		Form form6("Top Secret", 1, 1);
		std::cout << boss << std::endl;
		std::cout << form6 << std::endl;
		boss.signForm(form6);
		std::cout << form6 << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 7: Multiple signing attempts ===" << std::endl;
	try {
		Bureaucrat charlie("Charlie", 25);
		Form form7("Report", 30, 20);
		std::cout << charlie << std::endl;
		std::cout << form7 << std::endl;
		charlie.signForm(form7);
		charlie.signForm(form7);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
