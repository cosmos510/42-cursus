/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 09:46:25 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/13 09:57:58 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Fixed.hpp"


int main( void ) {
    Fixed a;
    Fixed b( a );
    Fixed c;
    c = b;

    std::cout << a.getRawBits() << std::endl;
    std::cout << b.getRawBits() << std::endl;
    std::cout << c.getRawBits() << std::endl;

    return 0;
}

/*
int main()
{
    std::cout << "1. Create a with default constructor\n";
    Fixed a;

    std::cout << "\n2. Create b by copying a (copy constructor)\n";
    Fixed b(a);

    std::cout << "\n3. Create c with default constructor\n";
    Fixed c;

    std::cout << "\n4. Assign b to c (copy assignment)\n";
    c = b;



    std::cout << "\n6. Print raw bits for a, b, c\n";
    std::cout << "a: " << a.getRawBits() << std::endl;
    std::cout << "b: " << b.getRawBits() << std::endl;
    std::cout << "c: " << c.getRawBits() << std::endl;

    std::cout << "\n7. Change c’s raw bits to 42\n";
    c.setRawBits(42);
	a = c;
    std::cout << "\n8. Print raw bits again\n";
    std::cout << "a: " << a.getRawBits() << std::endl;
    std::cout << "b: " << b.getRawBits() << std::endl;
    std::cout << "c: " << c.getRawBits() << std::endl;

    std::cout << "\nEnd of main, destructors called automatically\n";
    return 0;
}*/