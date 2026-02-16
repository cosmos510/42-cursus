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
#include "Intern.hpp"
#include "AForm.hpp"
#include <iostream>

int main() {
	Intern intern;
	Bureaucrat boss("Boss", 1);

	std::cout << "=== TEST 1: Create shrubbery creation ===" << std::endl;
	{
		AForm* form = intern.makeForm("shrubbery creation", "garden");
		if (form) {
			std::cout << *form << std::endl;
			boss.signForm(*form);
			boss.executeForm(*form);
			delete form;
		}
	}

	std::cout << "\n=== TEST 2: Create robotomy request ===" << std::endl;
	{
		AForm* form = intern.makeForm("robotomy request", "Bender");
		if (form) {
			std::cout << *form << std::endl;
			boss.signForm(*form);
			boss.executeForm(*form);
			delete form;
		}
	}

	std::cout << "\n=== TEST 3: Create presidential pardon ===" << std::endl;
	{
		AForm* form = intern.makeForm("presidential pardon", "Arthur");
		if (form) {
			std::cout << *form << std::endl;
			boss.signForm(*form);
			boss.executeForm(*form);
			delete form;
		}
	}

	std::cout << "\n=== TEST 4: Invalid form name ===" << std::endl;
	{
		AForm* form = intern.makeForm("invalid form", "target");
		if (form)
			delete form;
	}

	std::cout << "\n=== TEST 5: Case sensitivity ===" << std::endl;
	{
		AForm* form = intern.makeForm("SHRUBBERY CREATION", "test");
		if (form)
			delete form;
	}

	std::cout << "\n=== TEST 6: Multiple forms ===" << std::endl;
	{
		AForm* forms[3];
		forms[0] = intern.makeForm("shrubbery creation", "home");
		forms[1] = intern.makeForm("robotomy request", "Robot");
		forms[2] = intern.makeForm("presidential pardon", "Prisoner");
		
		for (int i = 0; i < 3; i++) {
			if (forms[i]) {
				boss.signForm(*forms[i]);
				boss.executeForm(*forms[i]);
				delete forms[i];
			}
		}
	}

	return 0;
}
