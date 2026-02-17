/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:15:19 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/17 18:15:20 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <stack>
#include <sstream>
#include <stdexcept>

RPN::RPN() {}

RPN::RPN(const RPN& other) { (void)other; }

RPN& RPN::operator=(const RPN& other) {
    (void)other;
    return *this;
}

RPN::~RPN() {}

int RPN::calculate(const std::string& expression) {
    std::stack<int> stack;
    std::istringstream iss(expression);
    std::string token;
    
    while (iss >> token) {
        if (token.length() == 1 && (token[0] == '+' || token[0] == '-' || 
            token[0] == '*' || token[0] == '/')) {
            if (stack.size() < 2)
                throw std::runtime_error("Error");
            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();
            if (token[0] == '+') stack.push(a + b);
            else if (token[0] == '-') stack.push(a - b);
            else if (token[0] == '*') stack.push(a * b);
            else if (token[0] == '/') {
                if (b == 0)
                    throw std::runtime_error("Error");
                stack.push(a / b);
            }
        } else if (token.length() == 1 && token[0] >= '0' && token[0] <= '9') {
            stack.push(token[0] - '0');
        } else {
            throw std::runtime_error("Error");
        }
    }
    
    if (stack.size() != 1)
        throw std::runtime_error("Error");
    
    return stack.top();
}
