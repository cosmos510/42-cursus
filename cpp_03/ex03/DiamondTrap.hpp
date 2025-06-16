/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:28:14 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 22:34:12 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIAMONDTrap_HPP
#define DIAMONDTrap_HPP
#include <iostream>
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class DiamondTrap : public FragTrap, public ScavTrap
{
	private:
		std::string name;
	public:
	// Constructeurs et destructeur
		DiamondTrap();
		DiamondTrap(std::string name);
		DiamondTrap(const DiamondTrap& value);
		~DiamondTrap();

		// Opérateur d’affectation
		DiamondTrap& operator=(const DiamondTrap&);
	
		void attack(const std::string& target);
		void whoAmI();

};

#endif