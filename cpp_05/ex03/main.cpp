/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:19:16 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/16 18:19:20 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include <cstdlib>
#include <ctime>

int main() {
	std::srand(std::time(0));
	Intern someRandomIntern;

	std::cout << "=== Test 1: Create robotomy request ===" << std::endl;
	{
		AForm* rrf;
		rrf = someRandomIntern.makeForm("robotomy request", "Bender");
		if (rrf) {
			std::cout << *rrf << std::endl;
			Bureaucrat bob("Bob", 1);
			bob.signForm(*rrf);
			bob.executeForm(*rrf);
			delete rrf;
		}
	}

	std::cout << "\n=== Test 2: Create shrubbery creation ===" << std::endl;
	{
		AForm* scf;
		scf = someRandomIntern.makeForm("shrubbery creation", "garden");
		if (scf) {
			std::cout << *scf << std::endl;
			Bureaucrat alice("Alice", 1);
			alice.signForm(*scf);
			alice.executeForm(*scf);
			delete scf;
		}
	}

	std::cout << "\n=== Test 3: Create presidential pardon ===" << std::endl;
	{
		AForm* ppf;
		ppf = someRandomIntern.makeForm("presidential pardon", "Arthur Dent");
		if (ppf) {
			std::cout << *ppf << std::endl;
			Bureaucrat boss("Boss", 1);
			boss.signForm(*ppf);
			boss.executeForm(*ppf);
			delete ppf;
		}
	}

	std::cout << "\n=== Test 4: Invalid form name ===" << std::endl;
	{
		AForm* invalid;
		invalid = someRandomIntern.makeForm("invalid form", "target");
		if (invalid) {
			std::cout << *invalid << std::endl;
			delete invalid;
		} else {
			std::cout << "Form creation failed as expected" << std::endl;
		}
	}

	std::cout << "\n=== Test 5: Another invalid form ===" << std::endl;
	{
		AForm* invalid2;
		invalid2 = someRandomIntern.makeForm("tax evasion", "target");
		if (invalid2) {
			std::cout << *invalid2 << std::endl;
			delete invalid2;
		} else {
			std::cout << "Form creation failed as expected" << std::endl;
		}
	}

	std::cout << "\n=== Test 6: Multiple forms ===" << std::endl;
	{
		AForm* forms[3];
		forms[0] = someRandomIntern.makeForm("robotomy request", "Target1");
		forms[1] = someRandomIntern.makeForm("shrubbery creation", "Target2");
		forms[2] = someRandomIntern.makeForm("presidential pardon", "Target3");
		
		Bureaucrat executor("Executor", 1);
		for (int i = 0; i < 3; i++) {
			if (forms[i]) {
				std::cout << *forms[i] << std::endl;
				executor.signForm(*forms[i]);
				executor.executeForm(*forms[i]);
				delete forms[i];
			}
		}
	}

	return 0;
}
