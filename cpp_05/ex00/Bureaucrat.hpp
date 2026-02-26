/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 08:28:55 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/18 11:08:25 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>
#include <exception>
#include <iostream>

class Bureaucrat {
private:
	const std::string _name;
	int _grade;

public:
	Bureaucrat();                                    // Default constructor
	Bureaucrat(const std::string& name, int grade);  // Parametrized constructor
	Bureaucrat(const Bureaucrat& other);             // Copy constructor
	Bureaucrat& operator=(const Bureaucrat& other);  // Copy assignment operator
	~Bureaucrat();                                   // Destructor

	// Getters
	const std::string& getName() const;
	int getGrade() const;

	// Member functions
	void incrementGrade();
	void decrementGrade();

	// Exception classes
	class GradeTooHighException : public std::exception {
	public:
		virtual const char* what() const throw();
	};

	class GradeTooLowException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
};

// Overload of insertion operator
std::ostream& operator<<(std::ostream& os, const Bureaucrat& b);

#endif
