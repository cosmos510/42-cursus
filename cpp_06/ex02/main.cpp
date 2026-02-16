/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 09:03:48 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/16 09:03:49 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Base* generate(void);
void identify(Base* p);
void identify(Base& p);

int main() {
	std::srand(std::time(0));

	std::cout << "=== Test 1: Generate and identify by pointer ===" << std::endl;
	for (int i = 0; i < 5; i++) {
		Base* obj = generate();
		std::cout << "Pointer: ";
		identify(obj);
		delete obj;
	}

	std::cout << "\n=== Test 2: Generate and identify by reference ===" << std::endl;
	for (int i = 0; i < 5; i++) {
		Base* obj = generate();
		std::cout << "Reference: ";
		identify(*obj);
		delete obj;
	}

	std::cout << "\n=== Test 3: Both methods on same object ===" << std::endl;
	Base* obj = generate();
	std::cout << "Pointer: ";
	identify(obj);
	std::cout << "Reference: ";
	identify(*obj);
	delete obj;

	return 0;
}
