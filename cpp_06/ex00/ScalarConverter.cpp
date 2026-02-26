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

static double parseChar(const std::string& literal) {
    if (literal.length() == 3)
        return static_cast<double>(literal[1]);
    return static_cast<double>(literal[0]);
}

static double parseSpecial(const std::string& literal) {
    if (literal.find('f') != std::string::npos)
        return strtof(literal.c_str(), NULL);
    return strtod(literal.c_str(), NULL);
}

static double parseFloat(const std::string& literal) {
    std::stringstream ss(literal.substr(0, literal.length() - 1));
    float f;
    if (!(ss >> f) || !ss.eof())
        throw std::runtime_error("Invalid float");
    return static_cast<double>(f);
}

static double parseDouble(const std::string& literal) {
    std::stringstream ss(literal);
    double d;
    if (!(ss >> d) || !ss.eof())
        throw std::runtime_error("Invalid double");
    return d;
}

static double parseInt(const std::string& literal) {
    char* end;
    errno = 0;
    long l = strtol(literal.c_str(), &end, 10);
    if (errno != 0 || *end != '\0' || l < std::numeric_limits<int>::min() || l > std::numeric_limits<int>::max())
        throw std::runtime_error("Invalid int");
    return static_cast<double>(l);
}

void ScalarConverter::convert(const std::string& literal) {
    try {
        double value;
        
        if (isChar(literal))
            value = parseChar(literal);
        else if (isSpecial(literal))
            value = parseSpecial(literal);
        else if (literal[literal.length() - 1] == 'f')
            value = parseFloat(literal);
        else if (literal.find('.') != std::string::npos)
            value = parseDouble(literal);
        else
            value = parseInt(literal);
        
        printAll(value);
    } catch (std::exception&) {
        std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible" << std::endl;
    }
}
