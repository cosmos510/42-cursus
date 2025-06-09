/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:32:50 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/06 17:23:54 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

const std::string& Weapon::getType()
{
	return type;
}

void Weapon::setType(std::string new_type)
{
	type = new_type;
}

Weapon::Weapon(std::string type)
{
	this->type = type;
}