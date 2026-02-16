#include "ScalarConverter.hpp"
#include <sstream>
#include <iomanip>
#include <cerrno>
#include <cstdlib>

ScalarConverter::ScalarConverter() {}

ScalarConverter::~ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other) {
    (void)other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) {
    (void)other;
    return *this;
}

static bool isCharLiteral(const std::string& literal)
{
    if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
        return true;
    
    if (literal.length() == 1 && std::isprint(literal[0]) && !std::isdigit(literal[0]))
        return true;
        
    return false;
}

static char getCharValue(const std::string& literal)
{
    if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
        return literal[1];
    else
        return literal[0];
}

static bool isFloatLiteral(const std::string& literal)
{
    return (literal.length() > 1 && literal[literal.length() - 1] == 'f');
}

static bool isSpecialLiteral(const std::string& literal)
{
    return (literal == "nan" || literal == "nanf" || 
            literal == "+inf" || literal == "+inff" ||
            literal == "-inf" || literal == "-inff");
}

static void handleSpecialLiterals(const std::string& literal, char& charValue, int& intValue, 
                                 float& floatValue, double& doubleValue,
                                 bool& charValid, bool& intValid, bool& floatValid, bool& doubleValid)
{
    (void)charValue;
    (void)intValue;
    charValid = false;
    intValid = false;
    floatValid = true;
    doubleValid = true;
    
    if (literal == "nan" || literal == "nanf")
    {
        floatValue = std::numeric_limits<float>::quiet_NaN();
        doubleValue = std::numeric_limits<double>::quiet_NaN();
    }
    else if (literal == "+inf" || literal == "+inff")
    {
        floatValue = std::numeric_limits<float>::infinity();
        doubleValue = std::numeric_limits<double>::infinity();
    }
    else if (literal == "-inf" || literal == "-inff")
    {
        floatValue = -std::numeric_limits<float>::infinity();
        doubleValue = -std::numeric_limits<double>::infinity();
    }
}

static void printResults(char charValue, int intValue, float floatValue, double doubleValue,
                        bool charValid, bool intValid, bool floatValid, bool doubleValid)
{
    if (!charValid)
        std::cout << "char: impossible" << std::endl;
    else if (!std::isprint(charValue))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << charValue << "'" << std::endl;
    if (!intValid)
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << intValue << std::endl;
    
    if (!floatValid)
        std::cout << "float: impossible" << std::endl;
    else
    {
        if (std::isnan(floatValue))
            std::cout << "float: nanf" << std::endl;
        else if (std::isinf(floatValue))
        {
            if (floatValue > 0)
                std::cout << "float: +inff" << std::endl;
            else
                std::cout << "float: -inff" << std::endl;
        }
        else
        {
            if (floatValue == static_cast<int>(floatValue))
                std::cout << "float: " << std::fixed << std::setprecision(1) << floatValue << "f" << std::endl;
            else
                std::cout << "float: " << floatValue << "f" << std::endl;
        }
    }
    
    if (!doubleValid)
        std::cout << "double: impossible" << std::endl;
    else
    {
        if (std::isnan(doubleValue))
            std::cout << "double: nan" << std::endl;
        else if (std::isinf(doubleValue))
        {
            if (doubleValue > 0)
                std::cout << "double: +inf" << std::endl;
            else
                std::cout << "double: -inf" << std::endl;
        }
        else
        {
            if (doubleValue == static_cast<int>(doubleValue))
                std::cout << "double: " << std::fixed << std::setprecision(1) << doubleValue << std::endl;
            else
                std::cout << "double: " << doubleValue << std::endl;
        }
    }
}

void ScalarConverter::convert(const std::string& literal)
{
    char charValue = 0;
    int intValue = 0;
    float floatValue = 0.0f;
    double doubleValue = 0.0;
    
    bool charValid = true;
    bool intValid = true;
    bool floatValid = true;
    bool doubleValid = true;
    
    if (isSpecialLiteral(literal))
    {
        handleSpecialLiterals(literal, charValue, intValue, floatValue, doubleValue,
                            charValid, intValid, floatValid, doubleValid);
    }
    else if (isCharLiteral(literal))
    {
        charValue = getCharValue(literal);
        intValue = static_cast<int>(charValue);
        floatValue = static_cast<float>(charValue);
        doubleValue = static_cast<double>(charValue);
    }
    else if (isFloatLiteral(literal))
    {
        std::string floatStr = literal.substr(0, literal.length() - 1);
        std::stringstream ss(floatStr);
        if (ss >> floatValue && ss.eof())
        {
            doubleValue = static_cast<double>(floatValue);
            intValue = static_cast<int>(floatValue);
            charValue = static_cast<char>(intValue);
            
            if (floatValue > std::numeric_limits<int>::max() || floatValue < std::numeric_limits<int>::min())
                intValid = false;
            if (intValue > 127 || intValue < -128)
                charValid = false;
        }
        else
        {
            charValid = intValid = floatValid = doubleValid = false;
        }
    }
    else
    {
        std::stringstream ss(literal);
        if (literal.find('.') != std::string::npos)
        {
            if (ss >> doubleValue && ss.eof())
            {
                floatValue = static_cast<float>(doubleValue);
                intValue = static_cast<int>(doubleValue);
                charValue = static_cast<char>(intValue);
                
                if (doubleValue > std::numeric_limits<int>::max() || doubleValue < std::numeric_limits<int>::min())
                    intValid = false;
                if (intValue > 127 || intValue < -128)
                    charValid = false;
            }
            else
            {
                charValid = intValid = floatValid = doubleValid = false;
            }
        }
        else
        {
            if (ss >> intValue && ss.eof())
            {
                charValue = static_cast<char>(intValue);
                floatValue = static_cast<float>(intValue);
                doubleValue = static_cast<double>(intValue);
                
                if (intValue > 127 || intValue < -128)
                    charValid = false;
                else if (!std::isprint(static_cast<char>(intValue)))
                    charValid = true;
            }
            else
            {
                charValid = intValid = floatValid = doubleValid = false;
            }
        }
    }
    
    printResults(charValue, intValue, floatValue, doubleValue,
                charValid, intValid, floatValid, doubleValid);
}