/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:45:54 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/14 11:56:11 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain()
{
	std::cout << "Brain: default constructor called" << std::endl;
}

Brain::Brain(const Brain& value)
{
	std::copy(value.ideas, value.ideas + 100, ideas);
	std::cout << "Brain: copy constructor called" << std::endl;
}

Brain::~Brain()
{
	std::cout << "Brain: destructor called" << std::endl;
}

Brain& Brain::operator=(const Brain &value)
{
	if (this != &value)
	{
		std::copy(value.ideas, value.ideas + 100, ideas);
		std::cout << "Brain: copy assignment operator called" << std::endl;
	}
	return *this;
}

void Brain::setIdea(int index, const std::string& idea) {
	if (index >= 0 && index < 100)
		ideas[index] = idea;
}

const std::string& Brain::getIdea(int index) const {
	static const std::string empty = "";
	if (index >= 0 && index < 100)
		return ideas[index];
	return empty;
}