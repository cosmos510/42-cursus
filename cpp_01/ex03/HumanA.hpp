/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:39:16 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/06 16:46:29 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
#define  HUMANA_HPP
#include <iostream>
#include "Weapon.hpp"
class HumanA
{
	private:
		std::string _name;
		Weapon& _Weapon;
	public:
		HumanA(std::string name, Weapon& weapon);
		void attack();
};

#endif