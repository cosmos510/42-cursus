/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 09:18:22 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/16 09:18:23 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"
#include <iostream>
#include <string>

int main() {
	std::cout << "=== Test 1: Empty array ===" << std::endl;
	Array<int> empty;
	std::cout << "Size: " << empty.size() << std::endl;

	std::cout << "\n=== Test 2: Array with size ===" << std::endl;
	Array<int> intArray(5);
	std::cout << "Size: " << intArray.size() << std::endl;
	std::cout << "Default values: ";
	for (unsigned int i = 0; i < intArray.size(); i++)
		std::cout << intArray[i] << " ";
	std::cout << std::endl;

	std::cout << "\n=== Test 3: Modify elements ===" << std::endl;
	for (unsigned int i = 0; i < intArray.size(); i++)
		intArray[i] = i * 10;
	std::cout << "Modified values: ";
	for (unsigned int i = 0; i < intArray.size(); i++)
		std::cout << intArray[i] << " ";
	std::cout << std::endl;

	std::cout << "\n=== Test 4: Copy constructor ===" << std::endl;
	Array<int> copy(intArray);
	std::cout << "Copy size: " << copy.size() << std::endl;
	std::cout << "Copy values: ";
	for (unsigned int i = 0; i < copy.size(); i++)
		std::cout << copy[i] << " ";
	std::cout << std::endl;

	std::cout << "\n=== Test 5: Deep copy verification ===" << std::endl;
	intArray[0] = 999;
	std::cout << "Original[0]: " << intArray[0] << std::endl;
	std::cout << "Copy[0]: " << copy[0] << std::endl;

	std::cout << "\n=== Test 6: Assignment operator ===" << std::endl;
	Array<int> assigned;
	assigned = intArray;
	std::cout << "Assigned size: " << assigned.size() << std::endl;
	std::cout << "Assigned values: ";
	for (unsigned int i = 0; i < assigned.size(); i++)
		std::cout << assigned[i] << " ";
	std::cout << std::endl;

	std::cout << "\n=== Test 7: Out of bounds access ===" << std::endl;
	try {
		std::cout << intArray[100] << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception caught: out of bounds" << std::endl;
	}

	std::cout << "\n=== Test 8: String array ===" << std::endl;
	Array<std::string> strArray(3);
	strArray[0] = "Hello";
	strArray[1] = "World";
	strArray[2] = "!";
	std::cout << "String array: ";
	for (unsigned int i = 0; i < strArray.size(); i++)
		std::cout << strArray[i] << " ";
	std::cout << std::endl;

	std::cout << "\n=== Test 9: Const array ===" << std::endl;
	const Array<int> constArray(intArray);
	std::cout << "Const array[0]: " << constArray[0] << std::endl;

	return 0;
}
