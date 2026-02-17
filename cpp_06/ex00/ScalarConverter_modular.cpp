/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter_modular.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 12:52:26 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/17 12:52:27 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include "TypeDetector.hpp"
#include "Printer.hpp"
#include <sstream>
#include <cerrno>
#include <cstdlib>

ScalarConverter::ScalarConverter() {}
ScalarConverter::~ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return *this; }

void ScalarConverter::convert(const std::string& literal) {
    double value;

    if (isChar(literal)) {
        value = static_cast<double>(literal[1]);
        printAll(value);
        return;
    }

    if (isSpecial(literal)) {
        if (literal.find('f') != std::string::npos)
            value = strtof(literal.c_str(), NULL);
        else
            value = strtod(literal.c_str(), NULL);
        printAll(value);
        return;
    }

    if (literal[literal.length() - 1] == 'f') {
        std::stringstream ss(literal.substr(0, literal.length() - 1));
        float f;
        if (!(ss >> f) || !ss.eof()) {
            std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible" << std::endl;
            return;
        }
        value = static_cast<double>(f);
        printAll(value);
        return;
    }

    if (literal.find('.') != std::string::npos) {
        std::stringstream ss(literal);
        if (!(ss >> value) || !ss.eof()) {
            std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible" << std::endl;
            return;
        }
    } else {
        char* end;
        errno = 0;
        long l = strtol(literal.c_str(), &end, 10);
        if (errno != 0 || *end != '\0' || l < std::numeric_limits<int>::min() || l > std::numeric_limits<int>::max()) {
            std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible" << std::endl;
            return;
        }
        value = static_cast<double>(l);
    }

    printAll(value);
}
