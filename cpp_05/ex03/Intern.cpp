/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:18:55 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/19 09:59:58 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern() {}

Intern::Intern(const Intern& other) {
	(void)other;
}

Intern& Intern::operator=(const Intern& other) {
	(void)other;
	return *this;
}

Intern::~Intern() {}

AForm* Intern::makeShrubberyCreation(const std::string& target) {
	return new ShrubberyCreationForm(target);
}

AForm* Intern::makeRobotomyRequest(const std::string& target) {
	return new RobotomyRequestForm(target);
}

AForm* Intern::makePresidentialPardon(const std::string& target) {
	return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) {
	std::string formNames[] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};
	
	AForm* (Intern::*creators[])(const std::string&) = {
		&Intern::makeShrubberyCreation,
		&Intern::makeRobotomyRequest,
		&Intern::makePresidentialPardon
	};

	for (int i = 0; i < 3; i++) {
		if (formName == formNames[i]) {
			std::cout << "Intern creates " << formName << std::endl;
			return (this->*creators[i])(target);
		}
	}

	throw UnknownFormException();
}

const char* Intern::UnknownFormException::what() const throw() {
	return "Unknown form type";
}
