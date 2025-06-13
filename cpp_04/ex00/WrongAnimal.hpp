/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongWrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 23:34:13 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 23:34:15 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP
#include <iostream>

class WrongAnimal
{
	protected:
		std::string type;
	public:
		WrongAnimal();
		WrongAnimal(const WrongAnimal& value);
		virtual ~WrongAnimal();
		WrongAnimal& operator=(const WrongAnimal& value);
		virtual void makeSound() const;
		std::string getType() const;
};

#endif