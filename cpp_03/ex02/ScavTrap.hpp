/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 21:33:16 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 21:45:58 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP
#include <iostream>
#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap
{
	public:
	// Constructeurs et destructeur
		ScavTrap();
		ScavTrap(std::string name);
		ScavTrap(const ScavTrap& value);
		~ScavTrap();

		// Opérateur d’affectation
		ScavTrap& operator=(const ScavTrap&);
	
		void attack(const std::string& target);
		void guardGate();
};


#endif