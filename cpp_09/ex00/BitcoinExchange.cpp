/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:08:45 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/17 18:08:46 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _data(other._data) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other)
        _data = other._data;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

static bool isValidDate(const std::string& date) {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    for (size_t i = 0; i < date.length(); i++) {
        if (i != 4 && i != 7 && !isdigit(date[i]))
            return false;
    }
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());
    if (month < 1 || month > 12 || day < 1 || day > 31)
        return false;
    if (month == 2 && day > 29)
        return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;
    return true;
}

static float parseValue(const std::string& str, bool& valid) {
    valid = true;
    char* end;
    float value = strtof(str.c_str(), &end);
    if (*end != '\0' && *end != '\n')
        valid = false;
    return value;
}

void BitcoinExchange::loadDatabase(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open database file." << std::endl;
        exit(1);
    }
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        size_t pos = line.find(',');
        if (pos != std::string::npos) {
            std::string date = line.substr(0, pos);
            bool valid;
            float rate = parseValue(line.substr(pos + 1), valid);
            if (valid)
                _data[date] = rate;
        }
    }
    file.close();
}

void BitcoinExchange::processInput(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        size_t pos = line.find('|');
        if (pos == std::string::npos) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        std::string date = line.substr(0, pos);
        std::string valueStr = line.substr(pos + 1);
        while (!date.empty() && (date[date.length() - 1] == ' ' || date[date.length() - 1] == '\t'))
            date.erase(date.length() - 1);
        while (!valueStr.empty() && (valueStr[0] == ' ' || valueStr[0] == '\t'))
            valueStr.erase(0, 1);
        if (!isValidDate(date)) {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }
        bool valid;
        float value = parseValue(valueStr, valid);
        if (!valid) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (value < 0) {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        if (value > 1000) {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }
        std::map<std::string, float>::iterator it = _data.lower_bound(date);
        if (it == _data.end() || it->first != date) {
            if (it == _data.begin()) {
                std::cerr << "Error: no data available for this date." << std::endl;
                continue;
            }
            --it;
        }
        std::cout << date << " => " << value << " = " << (value * it->second) << std::endl;
    }
    file.close();
}
