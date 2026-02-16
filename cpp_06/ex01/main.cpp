/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 08:59:24 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/16 08:59:25 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include <iostream>

int main() {
	Data original;
	original.value = 42;
	original.name = "Test Data";

	std::cout << "Original Data:" << std::endl;
	std::cout << "  Address: " << &original << std::endl;
	std::cout << "  Value: " << original.value << std::endl;
	std::cout << "  Name: " << original.name << std::endl;

	uintptr_t serialized = Serializer::serialize(&original);
	std::cout << "\nSerialized: " << serialized << std::endl;

	Data* deserialized = Serializer::deserialize(serialized);
	std::cout << "\nDeserialized Data:" << std::endl;
	std::cout << "  Address: " << deserialized << std::endl;
	std::cout << "  Value: " << deserialized->value << std::endl;
	std::cout << "  Name: " << deserialized->name << std::endl;

	std::cout << "\nPointers equal: " << (deserialized == &original ? "YES" : "NO") << std::endl;

	return 0;
}
