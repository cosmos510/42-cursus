/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:13:27 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 22:01:07 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
int main()
{
    std::cout << "\n--- Testing ClapTrap ---\n" << std::endl;

    ClapTrap clap1("Clappy");
    ClapTrap clap2(clap1);
    ClapTrap clap3;
    clap3 = clap1;

    std::cout << "\n--- Testing ClapTrap actions ---\n" << std::endl;
    clap1.attack("Target A");
    clap1.takeDamage(3);
    clap1.beRepaired(5);

    std::cout << "\n--- Depleting ClapTrap energy ---\n" << std::endl;
    for (int i = 0; i < 12; ++i)
        clap1.attack("Energy Drain");

    std::cout << "\n--- Testing ClapTrap with 0 HP ---\n" << std::endl;
    clap1.takeDamage(100);
    clap1.beRepaired(10);

    std::cout << "\n--- Testing ScavTrap ---\n" << std::endl;

    ScavTrap scav1("Scavy");
    ScavTrap scav2(scav1);
    ScavTrap scav3;
    scav3 = scav1;

    std::cout << "\n--- Testing ScavTrap actions ---\n" << std::endl;
    scav1.attack("Target B");
    scav1.takeDamage(20);
    scav1.beRepaired(10);
    scav1.guardGate();

    std::cout << "\n--- Depleting ScavTrap energy ---\n" << std::endl;
    for (int i = 0; i < 55; ++i)
        scav1.attack("Energy Drain");

    std::cout << "\n--- Testing ScavTrap with 0 HP ---\n" << std::endl;
    scav1.takeDamage(200);
    scav1.guardGate();

    std::cout << "\n--- End of main ---\n" << std::endl;
    return 0;
}