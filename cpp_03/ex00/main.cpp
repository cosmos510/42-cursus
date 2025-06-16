/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:13:27 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 19:28:24 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main() {
    // Default constructor
    ClapTrap a;
    
    // Parameterized constructor
    ClapTrap b("Clappy");

    // Copy constructor
    ClapTrap c(b);

    // Assignment operator
    a = b;

    std::cout << "\n--- Testing attack() ---" << std::endl;
    b.attack("Enemy");
	

    std::cout << "\n--- Testing takeDamage() ---" << std::endl;
    b.takeDamage(3);

    std::cout << "\n--- Testing beRepaired() ---" << std::endl;
    b.beRepaired(5);

    std::cout << "\n--- Testing no energy attack() ---" << std::endl;
    for (int i = 0; i < 11; ++i) {
        b.attack("Target");
    }

    std::cout << "\n--- Testing no hit points repair() ---" << std::endl;
    b.takeDamage(100);
    b.beRepaired(10);

    return 0;
}