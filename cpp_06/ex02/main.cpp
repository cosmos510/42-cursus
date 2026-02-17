/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 09:03:48 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/17 12:51:45 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Base* generate(void);
void identify(Base* p);
void identify(Base& p);

int main() {
	std::srand(std::time(NULL));

	std::cout << "=== TEST 1: Generate and identify by pointer ===" << std::endl;
	for (int i = 0; i < 10; i++) {
		Base* ptr = generate();
		std::cout << "Test " << i + 1 << ": ";
		identify(ptr);
		delete ptr;
	}

	std::cout << "\n=== TEST 2: Generate and identify by reference ===" << std::endl;
	for (int i = 0; i < 10; i++) {
		Base* ptr = generate();
		std::cout << "Test " << i + 1 << ": ";
		identify(*ptr);
		delete ptr;
	}

	std::cout << "\n=== TEST 3: Specific types ===" << std::endl;
	{
		A a;
		B b;
		C c;
		
		std::cout << "A by pointer: ";
		identify(&a);
		std::cout << "A by reference: ";
		identify(a);
		
		std::cout << "B by pointer: ";
		identify(&b);
		std::cout << "B by reference: ";
		identify(b);
		
		std::cout << "C by pointer: ";
		identify(&c);
		std::cout << "C by reference: ";
		identify(c);
	}

	std::cout << "\n=== TEST 4: Polymorphism ===" << std::endl;
	{
		Base* bases[3];
		bases[0] = new A();
		bases[1] = new B();
		bases[2] = new C();
		
		for (int i = 0; i < 3; i++) {
			std::cout << "Base[" << i << "] by pointer: ";
			identify(bases[i]);
			std::cout << "Base[" << i << "] by reference: ";
			identify(*bases[i]);
			delete bases[i];
		}
	}

	return 0;
}

