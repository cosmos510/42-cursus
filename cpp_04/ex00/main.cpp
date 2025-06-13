/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 23:33:04 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 23:33:06 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main() {
	std::cout << "\n=== Correct Polymorphism Test ===" << std::endl;

	const Animal* meta = new Animal();
	const Animal* dog = new Dog();
	const Animal* cat = new Cat();

	std::cout << "Dog type: " << dog->getType() << std::endl;
	std::cout << "Cat type: " << cat->getType() << std::endl;

	std::cout << "Cat sound: "; cat->makeSound(); // Should print "Miaou"
	std::cout << "Dog sound: "; dog->makeSound(); // Should print "Wouaf"
	std::cout << "Animal sound: "; meta->makeSound(); // Generic

	delete meta;
	delete dog;
	delete cat;

	std::cout << "\n=== Copy and Assignment Tests ===" << std::endl;
	Cat kitty;
	Cat kittyClone(kitty); // Copy constructor
	Cat anotherKitty;
	anotherKitty = kitty;  // Assignment operator

	Dog doggo;
	Dog doggoClone(doggo); // Copy constructor
	Dog anotherDoggo;
	anotherDoggo = doggo;  // Assignment operator

	std::cout << "\n=== Wrong Polymorphism Test ===" << std::endl;

	const WrongAnimal* wAnimal = new WrongAnimal();
	const WrongAnimal* wCat = new WrongCat();

	std::cout << "WrongCat type: " << wCat->getType() << std::endl;

	std::cout << "WrongAnimal sound: "; wAnimal->makeSound();  // Generic sound
	std::cout << "WrongCat sound: "; wCat->makeSound();        // Still generic sound (no virtual)

	delete wAnimal;
	delete wCat;

	std::cout << "\n=== End of Main (Destructors called) ===" << std::endl;
	return 0;
}