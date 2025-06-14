/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 23:33:04 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/14 12:27:48 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main() {
    std::cout << "\n=== Creating Animals ===" << std::endl;
    const Animal* animals[4];

    for (int i = 0; i < 2; ++i)
        animals[i] = new Dog();
    for (int i = 2; i < 4; ++i)
        animals[i] = new Cat();

    std::cout << "\n=== Making Sounds ===" << std::endl;
    for (int i = 0; i < 4; ++i)
        animals[i]->makeSound();

    std::cout << "\n=== Deleting Animals ===" << std::endl;
    for (int i = 0; i < 4; ++i)
        delete animals[i];

    std::cout << "\n=== Testing Deep Copy ===" << std::endl;
    Dog dog1;
    dog1.setIdea(0, "Chase the cat");

    Dog dog2 = dog1; // Copy constructor

    std::cout << "Dog1 idea 0: " << dog1.getIdea(0) << std::endl;
    std::cout << "Dog2 idea 0 (copied): " << dog2.getIdea(0) << std::endl;

    dog2.setIdea(0, "Eat food");

    std::cout << "Dog1 idea 0 after Dog2 changes: " << dog1.getIdea(0) << std::endl;
    std::cout << "Dog2 idea 0 after change: " << dog2.getIdea(0) << std::endl;

    std::cout << "\n=== Testing WrongAnimal Polymorphism ===" << std::endl;
    const WrongAnimal* wrong = new WrongCat();
    std::cout << "Type: " << wrong->getType() << std::endl;
    wrong->makeSound(); // Will output WrongAnimal's sound

    delete wrong; // WrongCat destructor not called

    return 0;

}