/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 12:00:00 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/16 12:00:01 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

int main() {
	std::cout << "=== TEST 1: Basic serialization ===" << std::endl;
	{
		Data data;
		data.value = 42;
		data.name = "Test";
		
		std::cout << "Original address: " << &data << std::endl;
		std::cout << "Original value: " << data.value << std::endl;
		std::cout << "Original name: " << data.name << std::endl;
		
		uintptr_t raw = Serializer::serialize(&data);
		std::cout << "Serialized: " << raw << std::endl;
		
		Data* ptr = Serializer::deserialize(raw);
		std::cout << "Deserialized address: " << ptr << std::endl;
		std::cout << "Deserialized value: " << ptr->value << std::endl;
		std::cout << "Deserialized name: " << ptr->name << std::endl;
		
		std::cout << "Addresses match: " << (&data == ptr ? "YES" : "NO") << std::endl;
	}

	std::cout << "\n=== TEST 2: Multiple serializations ===" << std::endl;
	{
		Data d1, d2, d3;
		d1.value = 1;
		d2.value = 2;
		d3.value = 3;
		
		uintptr_t r1 = Serializer::serialize(&d1);
		uintptr_t r2 = Serializer::serialize(&d2);
		uintptr_t r3 = Serializer::serialize(&d3);
		
		std::cout << "d1: " << Serializer::deserialize(r1)->value << std::endl;
		std::cout << "d2: " << Serializer::deserialize(r2)->value << std::endl;
		std::cout << "d3: " << Serializer::deserialize(r3)->value << std::endl;
	}

	std::cout << "\n=== TEST 3: Null pointer ===" << std::endl;
	{
		Data* null = NULL;
		uintptr_t raw = Serializer::serialize(null);
		Data* ptr = Serializer::deserialize(raw);
		std::cout << "Null pointer: " << (ptr == NULL ? "NULL" : "NOT NULL") << std::endl;
	}

	std::cout << "\n=== TEST 4: Heap allocated ===" << std::endl;
	{
		Data* heap = new Data;
		heap->value = 999;
		heap->name = "Heap";
		
		uintptr_t raw = Serializer::serialize(heap);
		Data* ptr = Serializer::deserialize(raw);
		
		std::cout << "Value: " << ptr->value << std::endl;
		std::cout << "Name: " << ptr->name << std::endl;
		std::cout << "Match: " << (heap == ptr ? "YES" : "NO") << std::endl;
		
		delete heap;
	}

	return 0;
}
