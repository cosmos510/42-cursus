/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 08:29:18 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/16 08:29:19 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <cstdlib>
#include <ctime>

int main() {
	std::srand(std::time(0));

	std::cout << "=== Test 1: ShrubberyCreationForm ===" << std::endl;
	try {
		Bureaucrat bob("Bob", 137);
		ShrubberyCreationForm form("home");
		std::cout << bob << std::endl;
		std::cout << form << std::endl;
		bob.signForm(form);
		bob.executeForm(form);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 2: RobotomyRequestForm ===" << std::endl;
	try {
		Bureaucrat alice("Alice", 45);
		RobotomyRequestForm form("Bender");
		std::cout << alice << std::endl;
		std::cout << form << std::endl;
		alice.signForm(form);
		alice.executeForm(form);
		alice.executeForm(form);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 3: PresidentialPardonForm ===" << std::endl;
	try {
		Bureaucrat boss("Boss", 5);
		PresidentialPardonForm form("Arthur Dent");
		std::cout << boss << std::endl;
		std::cout << form << std::endl;
		boss.signForm(form);
		boss.executeForm(form);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 4: Execute without signing ===" << std::endl;
	try {
		Bureaucrat charlie("Charlie", 1);
		ShrubberyCreationForm form("garden");
		std::cout << charlie << std::endl;
		std::cout << form << std::endl;
		charlie.executeForm(form);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 5: Execute with insufficient grade ===" << std::endl;
	try {
		Bureaucrat lowGrade("LowGrade", 50);
		PresidentialPardonForm form("Ford Prefect");
		Bureaucrat signer("Signer", 1);
		std::cout << lowGrade << std::endl;
		std::cout << form << std::endl;
		signer.signForm(form);
		lowGrade.executeForm(form);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 6: Sign with insufficient grade ===" << std::endl;
	try {
		Bureaucrat intern("Intern", 150);
		RobotomyRequestForm form("Marvin");
		std::cout << intern << std::endl;
		std::cout << form << std::endl;
		intern.signForm(form);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
