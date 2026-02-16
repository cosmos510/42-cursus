/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 09:13:44 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/16 09:13:45 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"
#include <iostream>
#include <string>

template<typename T>
void print(T const & x) {
	std::cout << x << " ";
}

template<typename T>
void increment(T& x) {
	x++;
}

void toUpper(char& c) {
	if (c >= 'a' && c <= 'z')
		c -= 32;
}

int main() {
	std::cout << "=== Test 1: Print int array ===" << std::endl;
	int intArray[] = {1, 2, 3, 4, 5};
	iter(intArray, 5, print<int>);
	std::cout << std::endl;

	std::cout << "\n=== Test 2: Increment int array ===" << std::endl;
	iter(intArray, 5, increment<int>);
	iter(intArray, 5, print<int>);
	std::cout << std::endl;

	std::cout << "\n=== Test 3: Print string array ===" << std::endl;
	std::string strArray[] = {"Hello", "World", "Test"};
	iter(strArray, 3, print<std::string>);
	std::cout << std::endl;

	std::cout << "\n=== Test 4: Print char array ===" << std::endl;
	char charArray[] = {'a', 'b', 'c', 'd', 'e'};
	iter(charArray, 5, print<char>);
	std::cout << std::endl;

	std::cout << "\n=== Test 5: Convert to uppercase ===" << std::endl;
	iter(charArray, 5, toUpper);
	iter(charArray, 5, print<char>);
	std::cout << std::endl;

	std::cout << "\n=== Test 6: Print double array ===" << std::endl;
	double doubleArray[] = {1.1, 2.2, 3.3, 4.4};
	iter(doubleArray, 4, print<double>);
	std::cout << std::endl;

	return 0;
}
