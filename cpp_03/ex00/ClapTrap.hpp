/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:43:26 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 21:40:25 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP
#include <iostream>

class ClapTrap
{
        private:
                std::string name;
				int 		hit;
				int			energy;
				int			attack_p;

        public:
                // Constructeurs et destructeur
				ClapTrap();
                ClapTrap(std::string name);
                ClapTrap(const ClapTrap& value);
                ~ClapTrap();

                // Opérateur d’affectation
                ClapTrap& operator=(const ClapTrap&);

                void attack(const std::string& target);
                void takeDamage(unsigned int amount);
				void beRepaired(unsigned int amount);
};

#endif