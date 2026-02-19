/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 09:18:22 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/19 11:00:33 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class Person {
public:
	std::string name;
	int age;
	Person() : name(""), age(0) {}
	Person(std::string n, int a) : name(n), age(a) {}
};

struct Point {
	int x;
	int y;
};

int main() {
	std::cout << "=== TEST 1: Empty array ==="<< std::endl;
	{
		Array<int> empty;
		std::cout << "Size: " << empty.size() << std::endl;
		try {
			std::cout << empty[0] << std::endl;
		} catch (std::exception& e) {
			std::cout << "Exception: " << e.what() << std::endl;
		}
	}

	std::cout << "\n=== TEST 2: Array initialization ==="<< std::endl;
	{
		Array<int> arr(5);
		std::cout << "Size: " << arr.size() << std::endl;
		std::cout << "Values (should be 0): ";
		for (unsigned int i = 0; i < arr.size(); i++)
			std::cout << arr[i] << " ";
		std::cout << std::endl;
	}

	std::cout << "\n=== TEST 3: Modify elements ==="<< std::endl;
	{
		Array<int> arr(5);
		for (unsigned int i = 0; i < arr.size(); i++)
			arr[i] = i * 10;
		std::cout << "Modified: ";
		for (unsigned int i = 0; i < arr.size(); i++)
			std::cout << arr[i] << " ";
		std::cout << std::endl;
	}

	std::cout << "\n=== TEST 4: Deep copy (constructor) ==="<< std::endl;
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
		std::cout << "After copy[0] = 99:" << std::endl;
		std::cout << "  Original[0]: " << original[0] << " (should be 1)" << std::endl;
		std::cout << "  Copy[0]: " << copy[0] << " (should be 99)" << std::endl;
	}

	std::cout << "\n=== TEST 5: Deep copy (assignment) ==="<< std::endl;
	{
		Array<int> a(3);
		a[0] = 1;
		a[1] = 2;
		a[2] = 3;
		
		Array<int> b(5);
		for (unsigned int i = 0; i < b.size(); i++)
			b[i] = 99;
		
		std::cout << "Before assignment:" << std::endl;
		std::cout << "  A size: " << a.size() << std::endl;
		std::cout << "  B size: " << b.size() << std::endl;
		
		b = a;
		
		std::cout << "After b = a:" << std::endl;
		std::cout << "  A size: " << a.size() << std::endl;
		std::cout << "  B size: " << b.size() << " (should be 3)" << std::endl;
		
		b[0] = 42;
		std::cout << "After b[0] = 42:" << std::endl;
		std::cout << "  A[0]: " << a[0] << " (should be 1)" << std::endl;
		std::cout << "  B[0]: " << b[0] << " (should be 42)" << std::endl;
	}

	std::cout << "\n=== TEST 6: Self-assignment ==="<< std::endl;
	{
		Array<int> arr(3);
		arr[0] = 1;
		arr[1] = 2;
		arr[2] = 3;
		Array<int>& ref = arr;
		arr = ref;
		std::cout << "After self-assignment: ";
		for (unsigned int i = 0; i < arr.size(); i++)
			std::cout << arr[i] << " ";
		std::cout << "(should be 1 2 3)" << std::endl;
	}

	std::cout << "\n=== TEST 7: Out of bounds (positive) ==="<< std::endl;
	{
		Array<int> arr(5);
		try {
			std::cout << "Accessing arr[10]..." << std::endl;
			std::cout << arr[10] << std::endl;
			std::cout << "ERROR: Should have thrown exception!" << std::endl;
		} catch (std::exception& e) {
			std::cout << "Exception caught: " << e.what() << std::endl;
		}
	}

	std::cout << "\n=== TEST 8: Out of bounds (at size) ==="<< std::endl;
	{
		Array<int> arr(5);
		try {
			std::cout << "Accessing arr[5] (size is 5)..." << std::endl;
			std::cout << arr[5] << std::endl;
			std::cout << "ERROR: Should have thrown exception!" << std::endl;
		} catch (std::exception& e) {
			std::cout << "Exception caught: " << e.what() << std::endl;
		}
	}

	std::cout << "\n=== TEST 9: String array ==="<< std::endl;
	{
		Array<std::string> arr(3);
		std::cout << "Initial values: ";
		for (unsigned int i = 0; i < arr.size(); i++)
			std::cout << "[" << arr[i] << "] ";
		std::cout << "(should be empty)" << std::endl;
		
		arr[0] = "Hello";
		arr[1] = "World";
		arr[2] = "42";
		
		std::cout << "After assignment: ";
		for (unsigned int i = 0; i < arr.size(); i++)
			std::cout << arr[i] << " ";
		std::cout << std::endl;
	}

	std::cout << "\n=== TEST 10: Const array ==="<< std::endl;
	{
		Array<int> arr(3);
		arr[0] = 1;
		arr[1] = 2;
		arr[2] = 3;
		
		const Array<int>& constArr = arr;
		std::cout << "Const access: ";
		for (unsigned int i = 0; i < constArr.size(); i++)
			std::cout << constArr[i] << " ";
		std::cout << std::endl;
		
		try {
			std::cout << "Const out of bounds..." << std::endl;
			std::cout << constArr[10] << std::endl;
		} catch (std::exception& e) {
			std::cout << "Exception: " << e.what() << std::endl;
		}
	}

	std::cout << "\n=== TEST 11: Float array ==="<< std::endl;
	{
		Array<float> arr(5);
		for (unsigned int i = 0; i < arr.size(); i++)
			arr[i] = i * 1.5f;
		std::cout << "Float values: ";
		for (unsigned int i = 0; i < arr.size(); i++)
			std::cout << arr[i] << " ";
		std::cout << std::endl;
	}

	std::cout << "\n=== TEST 12: Large array ==="<< std::endl;
	{
		Array<int> arr(1000);
		std::cout << "Created array of size: " << arr.size() << std::endl;
		arr[0] = 1;
		arr[999] = 999;
		std::cout << "arr[0] = " << arr[0] << std::endl;
		std::cout << "arr[999] = " << arr[999] << std::endl;
	}

	std::cout << "\n=== TEST 13: Multiple assignments ==="<< std::endl;
	{
		Array<int> a(2);
		Array<int> b(3);
		Array<int> c(4);
		
		a[0] = 1; a[1] = 2;
		b[0] = 10; b[1] = 20; b[2] = 30;
		c[0] = 100; c[1] = 200; c[2] = 300; c[3] = 400;
		
		std::cout << "Before: a.size=" << a.size() << " b.size=" << b.size() << " c.size=" << c.size() << std::endl;
		
		a = b = c;
		
		std::cout << "After a=b=c: a.size=" << a.size() << " b.size=" << b.size() << " c.size=" << c.size() << std::endl;
		std::cout << "a[0]=" << a[0] << " b[0]=" << b[0] << " c[0]=" << c[0] << std::endl;
	}

	std::cout << "\n=== TEST 14: Random access ==="<< std::endl;
	{
		std::srand(std::time(NULL));
		Array<int> arr(10);
		
		for (unsigned int i = 0; i < arr.size(); i++)
			arr[i] = std::rand() % 100;
		
		std::cout << "Random values: ";
		for (unsigned int i = 0; i < arr.size(); i++)
			std::cout << arr[i] << " ";
		std::cout << std::endl;
	}

	std::cout << "\n=== TEST15: Const prevents modification ===" << std::endl;
	{
		Array<int> arr(3);
		arr[0] = 42;
		
		const Array<int>& constArr = arr;
		std::cout << constArr[0]<< std::endl;
		// constArr[0] = 99;
	}

	std::cout << "\n=== TEST 16: Complex type - Person class ==="<< std::endl;
	{
		Array<Person> people(3);
		people[0] = Person("Alice", 25);
		people[1] = Person("Bob", 30);
		people[2] = Person("Charlie", 35);
		
		std::cout << "People array:" << std::endl;
		for (unsigned int i = 0; i < people.size(); i++)
			std::cout << "  " << people[i].name << ", age " << people[i].age << std::endl;
	}

	std::cout << "\n=== TEST 17: Complex type - Point struct ==="<< std::endl;
	{
		Array<Point> points(3);
		points[0].x = 10; points[0].y = 20;
		points[1].x = 30; points[1].y = 40;
		points[2].x = 50; points[2].y = 60;
		
		std::cout << "Points array:" << std::endl;
		for (unsigned int i = 0; i < points.size(); i++)
			std::cout << "  Point(" << points[i].x << ", " << points[i].y << ")" << std::endl;
	}

	std::cout << "\n=== All tests completed ==="<< std::endl;
	return 0;
}

