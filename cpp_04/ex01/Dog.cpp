/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 23:22:18 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/14 12:13:09 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Brain.hpp"

Dog::Dog() : Animal(), brain(new Brain()) {
	type = "Dog";
	std::cout << "Dog: default constructor called" << std::endl;
}

Dog::Dog(const Dog& other) : Animal(other), brain(new Brain(*other.brain)) {
	type = other.type;
	std::cout << "Dog: copy constructor called" << std::endl;
}

Dog::~Dog() {
	delete brain;
	std::cout << "Dog: destructor called" << std::endl;
}

Dog& Dog::operator=(const Dog& other) {
	if (this != &other) {
		Animal::operator=(other);
		if (brain)
			delete brain;
		brain = new Brain(*other.brain);
	}
	std::cout << "Dog: copy assignment operator called" << std::endl;
	return *this;
}

void Dog::makeSound() const {
	std::cout << "Wouaf!" << std::endl;
}
void Dog::setIdea(int index, const std::string& idea) {
	brain->setIdea(index, idea);
}

std::string Dog::getIdea(int index) const {
	return brain->getIdea(index);
}