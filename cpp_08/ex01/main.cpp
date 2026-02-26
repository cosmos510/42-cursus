/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 10:30:00 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/16 10:30:01 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
	std::cout << "=== TEST 1: Subject example ===" << std::endl;
	{
		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}

	std::cout << "\n=== TEST 2: Exception - Full ===" << std::endl;
	{
		try {
			Span sp(3);
			sp.addNumber(1);
			sp.addNumber(2);
			sp.addNumber(3);
			sp.addNumber(4);
		} catch (std::exception& e) {
			std::cout << "Exception: " << e.what() << std::endl;
		}
	}

	std::cout << "\n=== TEST 3: Exception - No span (empty) ===" << std::endl;
	{
		try {
			Span sp(5);
			std::cout << sp.shortestSpan() << std::endl;
		} catch (std::exception& e) {
			std::cout << "Exception: " << e.what() << std::endl;
		}
	}

	std::cout << "\n=== TEST 4: Exception - No span (one element) ===" << std::endl;
	{
		try {
			Span sp(5);
			sp.addNumber(42);
			std::cout << sp.longestSpan() << std::endl;
		} catch (std::exception& e) {
			std::cout << "Exception: " << e.what() << std::endl;
		}
	}

	std::cout << "\n=== TEST 5: Range of iterators ===" << std::endl;
	{
		Span sp(10);
		std::vector<int> vec;
		for (int i = 0; i < 10; i++)
			vec.push_back(i * 2);
		sp.addNumber(vec.begin(), vec.end());
		std::cout << "Shortest: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest: " << sp.longestSpan() << std::endl;
	}

	std::cout << "\n=== TEST 6: 10,000 numbers ===" << std::endl;
	{
		std::srand(std::time(NULL));
		Span sp(10000);
		std::vector<int> vec;
		for (int i = 0; i < 10000; i++)
			vec.push_back(std::rand());
		sp.addNumber(vec.begin(), vec.end());
		std::cout << "Shortest: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest: " << sp.longestSpan() << std::endl;
	}

	std::cout << "\n=== TEST 7: 100,000 numbers ===" << std::endl;
	{
		Span sp(100000);
		std::vector<int> vec;
		for (int i = 0; i < 100000; i++)
			vec.push_back(i);
		sp.addNumber(vec.begin(), vec.end());
		std::cout << "Shortest: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest: " << sp.longestSpan() << std::endl;
	}

	std::cout << "\n=== TEST 8: Negative numbers ===" << std::endl;
	{
		Span sp(5);
		sp.addNumber(-10);
		sp.addNumber(-5);
		sp.addNumber(0);
		sp.addNumber(5);
		sp.addNumber(10);
		std::cout << "Shortest: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest: " << sp.longestSpan() << std::endl;
	}

	std::cout << "\n=== TEST 9: Duplicates ===" << std::endl;
	{
		Span sp(5);
		sp.addNumber(5);
		sp.addNumber(5);
		sp.addNumber(5);
		sp.addNumber(10);
		sp.addNumber(20);
		std::cout << "Shortest: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest: " << sp.longestSpan() << std::endl;
	}

	return 0;
}
