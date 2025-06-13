/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:13:27 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 22:18:59 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main() {
    std::cout << "=== Creating ClapTrap ===" << std::endl;
    ClapTrap clap("Clappy");

    std::cout << "\n=== Creating ScavTrap ===" << std::endl;
    ScavTrap scav("Scavvy");

    std::cout << "\n=== Creating FragTrap ===" << std::endl;
    FragTrap frag("Fraggy");

    std::cout << "\n=== Testing ClapTrap ===" << std::endl;
    clap.attack("Dummy");
    clap.takeDamage(4);
    clap.beRepaired(3);

    std::cout << "\n=== Testing ScavTrap ===" << std::endl;
    scav.attack("Dummy");
    scav.takeDamage(20);
    scav.beRepaired(15);
    scav.guardGate();

    std::cout << "\n=== Testing FragTrap ===" << std::endl;
    frag.attack("Dummy");
    frag.takeDamage(30);
    frag.beRepaired(25);
    frag.highFivesGuys();

    std::cout << "\n=== Destruction Begins ===" << std::endl;
    return 0;
}