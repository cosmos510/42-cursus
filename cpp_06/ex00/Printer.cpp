/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printer.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 12:52:35 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/17 12:52:36 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Printer.hpp"

void printChar(double d) {
    if (std::isnan(d) || std::isinf(d) || d < 0 || d > 127)
        std::cout << "char: impossible" << std::endl;
    else if (d < 32 || d == 127)
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;
}

void printInt(double d) {
    if (std::isnan(d) || std::isinf(d) || d < std::numeric_limits<int>::min() || d > std::numeric_limits<int>::max())
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(d) << std::endl;
}

void printFloat(double d) {
    float f = static_cast<float>(d);
    std::cout << "float: ";
    if (std::isnan(f))
        std::cout << "nanf";
    else if (std::isinf(f))
        std::cout << (f > 0 ? "+inff" : "-inff");
    else
        std::cout << std::fixed << std::setprecision(1) << f << "f";
    std::cout << std::endl;
}

void printDouble(double d) {
    std::cout << "double: ";
    if (std::isnan(d))
        std::cout << "nan";
    else if (std::isinf(d))
        std::cout << (d > 0 ? "+inf" : "-inf");
    else
        std::cout << std::fixed << std::setprecision(1) << d;
    std::cout << std::endl;
}

void printAll(double value) {
    printChar(value);
    printInt(value);
    printFloat(value);
    printDouble(value);
}
