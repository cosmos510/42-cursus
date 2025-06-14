/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 23:01:35 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/14 12:33:15 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include <iostream>

class Animal
{
	protected:
		std::string type;
		Animal();
		Animal(const Animal& value);
	public:
		virtual ~Animal();
		Animal& operator=(const Animal& value);
		virtual void makeSound() const = 0;
		std::string getType() const;
};

#endif