/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TypeDetector.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 12:52:19 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/17 12:52:20 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TypeDetector.hpp"

bool isChar(const std::string& str) {
    if (str.length() == 3 && str[0] == '\'' && str[2] == '\'')
        return true;
    if (str.length() == 1 && !std::isdigit(str[0]))
        return true;
    return false;
}

bool isSpecial(const std::string& str) {
    return str == "-inff" || str == "+inff" || str == "nanf" ||
           str == "-inf" || str == "+inf" || str == "nan";
}
