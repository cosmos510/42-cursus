/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 23:28:00 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/14 12:13:47 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Brain.hpp"

Cat::Cat() : Animal(), brain(new Brain()) {
	type = "Cat";
	std::cout << "Cat: default constructor called" << std::endl;
}

Cat::Cat(const Cat& other) : Animal(other), brain(new Brain(*other.brain)) {
	type = other.type;
	std::cout << "Cat: copy constructor called" << std::endl;
}

Cat::~Cat() {
	delete brain;
	std::cout << "Cat: destructor called" << std::endl;
}

Cat& Cat::operator=(const Cat& other) {
	if (this != &other) {
		Animal::operator=(other);
		if (brain)
			delete brain;
		brain = new Brain(*other.brain);
	}
	std::cout << "Cat: copy assignment operator called" << std::endl;
	return *this;
}

void Cat::makeSound() const {
	std::cout << "miaou!" << std::endl;
}

void Cat::setIdea(int index, const std::string& idea) {
	brain->setIdea(index, idea);
}

std::string Cat::getIdea(int index) const {
	return brain->getIdea(index);
}