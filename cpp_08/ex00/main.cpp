/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 10:00:00 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/16 09:24:09 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <deque>

template<typename T>
void printContainer(const T& container, const std::string& name) {
	std::cout << name << ": ";
	for (typename T::const_iterator it = container.begin(); it != container.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

template<typename T>
void testFind(T& container, int value) {
	try {
		typename T::iterator it = easyfind(container, value);
		std::cout << "  [OK] Found " << value << " at position " << std::distance(container.begin(), it) << std::endl;
	} catch (std::exception& e) {
		std::cout << "  [KO] " << value << ": " << e.what() << std::endl;
	}
}

int main() {
	std::cout << "=== TEST 1: Vector ==="<< std::endl;
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	printContainer(vec, "Vector");
	testFind(vec, 1);
	testFind(vec, 3);
	testFind(vec, 5);
	testFind(vec, 42);
	testFind(vec, 0);

	std::cout << "\n=== TEST 2: List ==="<< std::endl;
	std::list<int> lst;
	lst.push_back(10);
	lst.push_back(20);
	lst.push_back(30);
	lst.push_back(20);
	lst.push_back(40);
	printContainer(lst, "List");
	testFind(lst, 10);
	testFind(lst, 20);
	testFind(lst, 40);
	testFind(lst, 100);
	testFind(lst, -5);

	std::cout << "\n=== TEST 3: Deque ==="<< std::endl;
	std::deque<int> deq;
	deq.push_back(7);
	deq.push_back(8);
	deq.push_back(9);
	printContainer(deq, "Deque");
	testFind(deq, 7);
	testFind(deq, 9);
	testFind(deq, 15);

	std::cout << "\n=== TEST 4: Empty container ==="<< std::endl;
	std::vector<int> empty;
	printContainer(empty, "Empty vector");
	testFind(empty, 1);

	std::cout << "\n=== TEST 5: Single element ==="<< std::endl;
	std::vector<int> single;
	single.push_back(42);
	printContainer(single, "Single element");
	testFind(single, 42);
	testFind(single, 43);

	std::cout << "\n=== TEST 6: Negative numbers ==="<< std::endl;
	std::list<int> negative;
	negative.push_back(-10);
	negative.push_back(-5);
	negative.push_back(0);
	negative.push_back(5);
	negative.push_back(10);
	printContainer(negative, "Negative numbers");
	testFind(negative, -10);
	testFind(negative, 0);
	testFind(negative, 10);
	testFind(negative, -100);

	std::cout << "\n=== TEST 7: Duplicates (finds first) ==="<< std::endl;
	std::vector<int> duplicates;
	duplicates.push_back(5);
	duplicates.push_back(3);
	duplicates.push_back(5);
	duplicates.push_back(5);
	duplicates.push_back(1);
	printContainer(duplicates, "Duplicates");
	testFind(duplicates, 5);

	return 0;
}
