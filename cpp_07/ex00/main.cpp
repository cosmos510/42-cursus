/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 09:09:51 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/19 10:37:36 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "whatever.hpp"
#include <iostream>
#include <string>

class Person {
public:
    int age;
    Person(int a) : age(a) {}
    bool operator<(const Person& other) const { return age < other.age; }
    bool operator>(const Person& other) const { return age > other.age; }
};

int main() {
	std::cout << "=== TEST 1: Int swap ===" << std::endl;
	{
		int a = 2;
		int b = 3;
		std::cout << "Before: a = " << a << ", b = " << b << std::endl;
		::swap(a, b);
		std::cout << "After: a = " << a << ", b = " << b << std::endl;
	}

	std::cout << "\n=== TEST 2: Int min/max ===" << std::endl;
	{
		int a = 2;
		int b = 3;
		std::cout << "min(" << a << ", " << b << ") = " << ::min(a, b) << std::endl;
		std::cout << "max(" << a << ", " << b << ") = " << ::max(a, b) << std::endl;
	}

	std::cout << "\n=== TEST 3: String swap ===" << std::endl;
	{
		std::string a = "chaine1";
		std::string b = "chaine2";
		std::cout << "Before: a = " << a << ", b = " << b << std::endl;
		::swap(a, b);
		std::cout << "After: a = " << a << ", b = " << b << std::endl;
	}

	std::cout << "\n=== TEST 4: String min/max ===" << std::endl;
	{
		std::string a = "chaine1";
		std::string b = "chaine2";
		std::cout << "min = " << ::min(a, b) << std::endl;
		std::cout << "max = " << ::max(a, b) << std::endl;
	}

	std::cout << "\n=== TEST 5: Float ===" << std::endl;
	{
		float a = 3.14f;
		float b = 2.71f;
		std::cout << "Before: a = " << a << ", b = " << b << std::endl;
		::swap(a, b);
		std::cout << "After: a = " << a << ", b = " << b << std::endl;
		std::cout << "min = " << ::min(a, b) << std::endl;
		std::cout << "max = " << ::max(a, b) << std::endl;
	}

	std::cout << "\n=== TEST 6: Equal values ===" << std::endl;
	{
		int a = 42;
		int b = 42;
		std::cout << "min(" << a << ", " << b << ") = " << ::min(a, b) << std::endl;
		std::cout << "max(" << a << ", " << b << ") = " << ::max(a, b) << std::endl;
	}

	std::cout << "\n=== TEST 7: Negative numbers ===" << std::endl;
	{
		std::string c = "chaine1";
		std::string d = "chaine2";
		::swap(c, d);
		std::cout << "c = " << c << ", d = " << d << std::endl;
		std::cout << "min(" << c << ", " << d << ") = " << ::min(c, d) << std::endl;
		std::cout << "max(" << c << ", " << d << ") = " << ::max(c, d) << std::endl;
	}

	std::cout << "\n=== TEST 8: Complex type (Person) ===" << std::endl;
	{
		Person p1(25);
		Person p2(30);
		std::cout << "Before: p1.age = " << p1.age << ", p2.age = " << p2.age << std::endl;
		::swap(p1, p2);
		std::cout << "After: p1.age = " << p1.age << ", p2.age = " << p2.age << std::endl;
		Person youngest = ::min(p1, p2);
		Person oldest = ::max(p1, p2);
		std::cout << "Youngest age: " << youngest.age << std::endl;
		std::cout << "Oldest age: " << oldest.age << std::endl;
	}

	return 0;
}
/*int main( void ) {
int a = 2;
int b = 3;
::swap( a, b );
std::cout << "a = " << a << ", b = " << b << std::endl;
std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;
std::string c = "chaine1";
std::string d = "chaine2";
::swap(c, d);
std::cout << "c = " << c << ", d = " << d << std::endl;
std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;
return 0;
}*/