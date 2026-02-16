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
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

int main() {
	std::cout << "=== TEST 1: ShrubberyCreationForm ===" << std::endl;
	try {
		Bureaucrat bob("Bob", 137);
		ShrubberyCreationForm shrub("home");
		std::cout << shrub << std::endl;
		bob.signForm(shrub);
		bob.executeForm(shrub);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 2: RobotomyRequestForm ===" << std::endl;
	try {
		Bureaucrat alice("Alice", 45);
		RobotomyRequestForm robot("Bender");
		alice.signForm(robot);
		alice.executeForm(robot);
		alice.executeForm(robot);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 3: PresidentialPardonForm ===" << std::endl;
	try {
		Bureaucrat president("President", 5);
		PresidentialPardonForm pardon("Arthur Dent");
		president.signForm(pardon);
		president.executeForm(pardon);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 4: Execute without signing ===" << std::endl;
	try {
		Bureaucrat bob("Bob", 1);
		ShrubberyCreationForm shrub("garden");
		bob.executeForm(shrub);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 5: Sign but grade too low to execute ===" << std::endl;
	try {
		Bureaucrat signer("Signer", 5);
		Bureaucrat executor("Executor", 50);
		PresidentialPardonForm pardon("Zaphod");
		signer.signForm(pardon);
		executor.executeForm(pardon);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 6: Grade too low to sign ===" << std::endl;
	try {
		Bureaucrat intern("Intern", 150);
		ShrubberyCreationForm shrub("office");
		intern.signForm(shrub);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== TEST 7: Polymorphism ===" << std::endl;
	{
		Bureaucrat boss("Boss", 1);
		AForm* forms[3];
		forms[0] = new ShrubberyCreationForm("park");
		forms[1] = new RobotomyRequestForm("Target");
		forms[2] = new PresidentialPardonForm("Criminal");
		
		for (int i = 0; i < 3; i++) {
			boss.signForm(*forms[i]);
			boss.executeForm(*forms[i]);
			delete forms[i];
		}
	}

	return 0;
}
