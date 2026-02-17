/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter_clean.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 12:52:29 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/17 12:52:30 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <sstream>
#include <iomanip>
#include <cerrno>
#include <cstdlib>

ScalarConverter::ScalarConverter() {}
ScalarConverter::~ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return *this; }

static bool isChar(const std::string& str) {
    return str.length() == 3 && str[0] == '\'' && str[2] == '\'';
}

static bool isSpecial(const std::string& str) {
    return str == "-inff" || str == "+inff" || str == "nanf" ||
           str == "-inf" || str == "+inf" || str == "nan";
}

static void printChar(double d) {
    if (std::isnan(d) || std::isinf(d) || d < 0 || d > 127)
        std::cout << "char: impossible" << std::endl;
    else if (d < 32 || d == 127)
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;
}

static void printInt(double d) {
    if (std::isnan(d) || std::isinf(d) || d < std::numeric_limits<int>::min() || d > std::numeric_limits<int>::max())
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(d) << std::endl;
}

static void printFloat(double d) {
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

static void printDouble(double d) {
    std::cout << "double: ";
    if (std::isnan(d))
        std::cout << "nan";
    else if (std::isinf(d))
        std::cout << (d > 0 ? "+inf" : "-inf");
    else
        std::cout << std::fixed << std::setprecision(1) << d;
    std::cout << std::endl;
}

static void printAll(double value) {
    printChar(value);
    printInt(value);
    printFloat(value);
    printDouble(value);
}

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
