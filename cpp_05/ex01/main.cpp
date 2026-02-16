/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:16:51 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/16 18:16:52 by maximemarti      ###   ########.fr       */
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

	std::cout << "\n=== TEST 2: Form grade too high (sign) ===" << std::endl;
	try {
		Form invalid("Invalid", 0, 50);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 3: Form grade too high (exec) ===" << std::endl;
	try {
		Form invalid("Invalid", 50, 0);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 4: Form grade too low (sign) ===" << std::endl;
	try {
		Form invalid("Invalid", 151, 50);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 5: Form grade too low (exec) ===" << std::endl;
	try {
		Form invalid("Invalid", 50, 151);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 6: Successful signing ===" << std::endl;
	try {
		Bureaucrat bob("Bob", 30);
		Form form("Contract", 50, 25);
		std::cout << "Before: " << form << std::endl;
		bob.signForm(form);
		std::cout << "After: " << form << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 7: Failed signing (grade too low) ===" << std::endl;
	try {
		Bureaucrat intern("Intern", 100);
		Form form("Top Secret", 50, 25);
		std::cout << "Before: " << form << std::endl;
		intern.signForm(form);
		std::cout << "After: " << form << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 8: Sign already signed form ===" << std::endl;
	try {
		Bureaucrat alice("Alice", 1);
		Form form("Document", 50, 25);
		alice.signForm(form);
		alice.signForm(form);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 9: Different bureaucrats sign same form ===" << std::endl;
	try {
		Bureaucrat boss("Boss", 1);
		Bureaucrat manager("Manager", 25);
		Form form("Report", 30, 20);
		boss.signForm(form);
		manager.signForm(form);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 10: Exact grade match ===" << std::endl;
	try {
		Bureaucrat exact("Exact", 50);
		Form form("Exact Form", 50, 25);
		std::cout << "Bureaucrat: " << exact << std::endl;
		std::cout << "Form: " << form << std::endl;
		exact.signForm(form);
		std::cout << "After: " << form << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 11: One grade too low ===" << std::endl;
	try {
		Bureaucrat almostGood("AlmostGood", 51);
		Form form("Strict Form", 50, 25);
		std::cout << "Bureaucrat: " << almostGood << std::endl;
		std::cout << "Form: " << form << std::endl;
		almostGood.signForm(form);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 12: Copy constructor ===" << std::endl;
	{
		Form original("Original", 50, 25);
		Bureaucrat signer("Signer", 1);
		signer.signForm(original);
		Form copy(original);
		std::cout << "Original: " << original << std::endl;
		std::cout << "Copy: " << copy << std::endl;
	}

	std::cout << "\n=== TEST 13: Assignment operator ===" << std::endl;
	{
		Form form1("Form1", 50, 25);
		Form form2("Form2", 100, 75);
		Bureaucrat signer("Signer", 1);
		signer.signForm(form1);
		std::cout << "Before assignment:" << std::endl;
		std::cout << "Form1: " << form1 << std::endl;
		std::cout << "Form2: " << form2 << std::endl;
		form2 = form1;
		std::cout << "After assignment:" << std::endl;
		std::cout << "Form2: " << form2 << std::endl;
	}

	std::cout << "\n=== TEST 14: Boundary values ===" << std::endl;
	try {
		Form highest("Highest", 1, 1);
		Form lowest("Lowest", 150, 150);
		std::cout << highest << std::endl;
		std::cout << lowest << std::endl;
		Bureaucrat president("President", 1);
		Bureaucrat intern("Intern", 150);
		president.signForm(highest);
		intern.signForm(lowest);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 15: Multiple forms, one bureaucrat ===" << std::endl;
	try {
		Bureaucrat worker("Worker", 50);
		Form form1("Form1", 60, 30);
		Form form2("Form2", 50, 25);
		Form form3("Form3", 40, 20);
		worker.signForm(form1);
		worker.signForm(form2);
		worker.signForm(form3);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
