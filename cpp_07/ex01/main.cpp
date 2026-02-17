/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 09:13:44 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/17 17:11:20 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"
#include <iostream>
#include <string>

template<typename T>
void print(T& x) {
	std::cout << x << " ";
}

template<typename T>
void increment(T& x) {
	x++;
}

template<typename T>
void square(T& x) {
	x = x * x;
}

template<typename T>
void plus_one(T& x) {
	x = x + 1;
}

int main() {
	std::cout << "=== TEST 1: Int array with print ===" << std::endl;
	{
		int arr[] = {1, 2, 3, 4, 5};
		iter(arr, 5, print<int>);
		std::cout << std::endl;
	}

	std::cout << "\n=== TEST 2: Int array with increment ===" << std::endl;
	{
		int arr[] = {1, 2, 3, 4, 5};
		std::cout << "Before: ";
		iter(arr, 5, print<int>);
		std::cout << std::endl;
		iter(arr, 5, increment<int>);
		std::cout << "After: ";
		iter(arr, 5, print<int>);
		std::cout << std::endl;
	}

	std::cout << "\n=== TEST 3: String array ===" << std::endl;
	{
		std::string arr[] = {"Hello", "World", "42"};
		iter(arr, 3, print<std::string>);
		std::cout << std::endl;
	}

	std::cout << "\n=== TEST 4: Float array ===" << std::endl;
	{
		float arr[] = {1.1f, 2.2f, 3.3f, 4.4f};
		iter(arr, 4, print<float>);
		std::cout << std::endl;
	}

	std::cout << "\n=== TEST 5: Empty array ===" << std::endl;
	{
		int arr[] = {1};
		iter(arr, 0, print<int>);
		std::cout << "(nothing printed)" << std::endl;
	}

	std::cout << "\n=== TEST 6: Square function ===" << std::endl;
	{
		int arr[] = {1, 2, 3, 4, 5};
		std::cout << "Before: ";
		iter(arr, 5, print<int>);
		std::cout << std::endl;
		iter(arr, 5, square<int>);
		std::cout << "After: ";
		iter(arr, 5, print<int>);
		std::cout << std::endl;
		iter(arr, 5, plus_one<int>);
		std::cout << "After plus one: ";
		iter(arr, 5, print<int>);
		
		std::cout << std::endl;
	}

	std::cout << "\n=== TEST 7: Char array ===" << std::endl;
	{
		char arr[] = {'a', 'b', 'c', 'd', 'e'};
		iter(arr, 5, print<char>);
		std::cout << std::endl;
	}

	return 0;
}

