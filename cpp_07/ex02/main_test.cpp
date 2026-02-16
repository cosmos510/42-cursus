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

#include "Array.hpp"
#include <iostream>
#include <string>

int main() {
	std::cout << "=== TEST 1: Empty array ===" << std::endl;
	{
		Array<int> empty;
		std::cout << "Size: " << empty.size() << std::endl;
	}

	std::cout << "\n=== TEST 2: Array with size ===" << std::endl;
	{
		Array<int> arr(5);
		std::cout << "Size: " << arr.size() << std::endl;
		for (unsigned int i = 0; i < arr.size(); i++)
			std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
	}

	std::cout << "\n=== TEST 3: Modify elements ===" << std::endl;
	{
		Array<int> arr(5);
		for (unsigned int i = 0; i < arr.size(); i++)
			arr[i] = i * 10;
		for (unsigned int i = 0; i < arr.size(); i++)
			std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
	}

	std::cout << "\n=== TEST 4: Copy constructor ===" << std::endl;
	{
		Array<int> original(3);
		original[0] = 1;
		original[1] = 2;
		original[2] = 3;
		
		Array<int> copy(original);
		std::cout << "Original: ";
		for (unsigned int i = 0; i < original.size(); i++)
			std::cout << original[i] << " ";
		std::cout << std::endl;
		
		std::cout << "Copy: ";
		for (unsigned int i = 0; i < copy.size(); i++)
			std::cout << copy[i] << " ";
		std::cout << std::endl;
		
		copy[0] = 99;
		std::cout << "After modifying copy[0]:" << std::endl;
		std::cout << "Original[0]: " << original[0] << std::endl;
		std::cout << "Copy[0]: " << copy[0] << std::endl;
	}

	std::cout << "\n=== TEST 5: Assignment operator ===" << std::endl;
	{
		Array<int> a(3);
		a[0] = 1;
		a[1] = 2;
		a[2] = 3;
		
		Array<int> b(5);
		b = a;
		
		std::cout << "A size: " << a.size() << std::endl;
		std::cout << "B size: " << b.size() << std::endl;
		
		b[0] = 99;
		std::cout << "After modifying b[0]:" << std::endl;
		std::cout << "A[0]: " << a[0] << std::endl;
		std::cout << "B[0]: " << b[0] << std::endl;
	}

	std::cout << "\n=== TEST 6: Out of bounds ===" << std::endl;
	{
		Array<int> arr(5);
		try {
			std::cout << arr[10] << std::endl;
		} catch (std::exception& e) {
			std::cout << "Exception caught: out of bounds" << std::endl;
		}
	}

	std::cout << "\n=== TEST 7: String array ===" << std::endl;
	{
		Array<std::string> arr(3);
		arr[0] = "Hello";
		arr[1] = "World";
		arr[2] = "42";
		
		for (unsigned int i = 0; i < arr.size(); i++)
			std::cout << arr[i] << " ";
		std::cout << std::endl;
	}

	std::cout << "\n=== TEST 8: Const array ===" << std::endl;
	{
		Array<int> arr(3);
		arr[0] = 1;
		arr[1] = 2;
		arr[2] = 3;
		
		const Array<int>& constArr = arr;
		for (unsigned int i = 0; i < constArr.size(); i++)
			std::cout << constArr[i] << " ";
		std::cout << std::endl;
	}

	return 0;
}
