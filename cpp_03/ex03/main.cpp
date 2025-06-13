/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:13:27 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 22:51:30 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "DiamondTrap.hpp"


int main()
{
    std::cout << "=== Creating ClapTrap ===" << std::endl;
    ClapTrap clap("Clappy");
    clap.attack("Target");
    clap.takeDamage(5);
    clap.beRepaired(3);

    std::cout << "\n=== Creating ScavTrap ===" << std::endl;
    ScavTrap scav("Scavvy");
    scav.attack("Enemy");
    scav.guardGate();

    std::cout << "\n=== Creating FragTrap ===" << std::endl;
    FragTrap frag("Fraggy");
    frag.attack("Monster");
    frag.highFivesGuys();

    std::cout << "\n=== Creating DiamondTrap ===" << std::endl;
    DiamondTrap diamond("Diamondy");

    // Show construction chaining
    std::cout << "\n=== DiamondTrap Actions ===" << std::endl;
    diamond.attack("Boss");      // uses ScavTrap attack
    diamond.takeDamage(20);      // inherited from ClapTrap
    diamond.beRepaired(10);      // inherited from ClapTrap
    diamond.highFivesGuys();     // from FragTrap
    diamond.guardGate();         // from ScavTrap
    diamond.whoAmI();            // DiamondTrap special

    std::cout << "\n=== Testing copy and assignment ===" << std::endl;
    DiamondTrap copyDiamond(diamond);    // copy constructor
    copyDiamond.whoAmI();

    DiamondTrap assignDiamond;
    assignDiamond = diamond;              // assignment operator
    assignDiamond.whoAmI();

    std::cout << "\n=== End of main, destructors will be called ===" << std::endl;

    return 0;
}