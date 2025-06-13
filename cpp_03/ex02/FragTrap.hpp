/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:09:47 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 22:13:44 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP
#include <iostream>
#include "ClapTrap.hpp"

class FragTrap : public ClapTrap
{
	public:
	// Constructeurs et destructeur
		FragTrap();
		FragTrap(std::string name);
		FragTrap(const FragTrap& value);
		~FragTrap();

		// Opérateur d’affectation
		FragTrap& operator=(const FragTrap&);
	
		void attack(const std::string& target);
		void highFivesGuys(void);
};


#endif