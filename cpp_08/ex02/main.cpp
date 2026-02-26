/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 11:00:00 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/16 11:00:01 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <iostream>
#include <list>

int main() {
	std::cout << "=== TEST 1: Subject example with MutantStack ===" << std::endl;
	{
		MutantStack<int> mstack;
		mstack.push(5);
		mstack.push(17);
		std::cout << mstack.top() << std::endl;
		mstack.pop();
		std::cout << mstack.size() << std::endl;
		mstack.push(3);
		mstack.push(5);
		mstack.push(737);
		mstack.push(0);
		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();
		++it;
		--it;
		while (it != ite) {
			std::cout << *it << std::endl;
			++it;
		}
		std::stack<int> s(mstack);
	}

	std::cout << "\n=== TEST 2: Same test with std::list ===" << std::endl;
	{
		std::list<int> mstack;
		mstack.push_back(5);
		mstack.push_back(17);
		std::cout << mstack.back() << std::endl;
		mstack.pop_back();
		std::cout << mstack.size() << std::endl;
		mstack.push_back(3);
		mstack.push_back(5);
		mstack.push_back(737);
		mstack.push_back(0);
		std::list<int>::iterator it = mstack.begin();
		std::list<int>::iterator ite = mstack.end();
		++it;
		--it;
		while (it != ite) {
			std::cout << *it << std::endl;
			++it;
		}
	}

	std::cout << "\n=== TEST 3: Copy constructor ===" << std::endl;
	{
		MutantStack<int> mstack;
		mstack.push(1);
		mstack.push(2);
		mstack.push(3);
		MutantStack<int> copy(mstack);
		std::cout << "Original top: " << mstack.top() << std::endl;
		std::cout << "Copy top: " << copy.top() << std::endl;
		copy.push(4);
		std::cout << "After push on copy:" << std::endl;
		std::cout << "Original size: " << mstack.size() << std::endl;
		std::cout << "Copy size: " << copy.size() << std::endl;
	}

	std::cout << "\n=== TEST 4: Assignment operator ===" << std::endl;
	{
		MutantStack<int> mstack;
		mstack.push(10);
		mstack.push(20);
		MutantStack<int> assigned;
		assigned.push(99);
		assigned = mstack;
		std::cout << "Assigned top: " << assigned.top() << std::endl;
		std::cout << "Assigned size: " << assigned.size() << std::endl;
	}

	std::cout << "\n=== TEST 5: Iterate and modify ===" << std::endl;
	{
		MutantStack<int> mstack;
		for (int i = 0; i < 5; i++)
			mstack.push(i);
		std::cout << "Before: ";
		for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
		for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
			*it *= 2;
		std::cout << "After (*2): ";
		for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}

	std::cout << "\n=== TEST 6: String MutantStack ===" << std::endl;
	{
		MutantStack<std::string> mstack;
		mstack.push("Hello");
		mstack.push("World");
		mstack.push("42");
		for (MutantStack<std::string>::iterator it = mstack.begin(); it != mstack.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}

	return 0;
}
