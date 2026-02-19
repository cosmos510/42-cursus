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
#include <sstream>
#include <stdexcept>
#include <cctype>

RPN::RPN() {}

RPN::RPN(const RPN& other) { (void)other; }

RPN& RPN::operator=(const RPN& other) {
    (void)other;
    return *this;
}

RPN::~RPN() {}

bool RPN::isOperator(const std::string& token) {
    return token.length() == 1 && 
           (token[0] == '+' || token[0] == '-' || 
            token[0] == '*' || token[0] == '/');
}

bool RPN::isNumber(const std::string& token) {
    return token.length() == 1 && std::isdigit(token[0]);
}

void RPN::applyOperator(std::stack<int>& stack, char op) {
    if (stack.size() < 2)
        throw std::runtime_error("Error");
    
    int b = stack.top(); stack.pop();
    int a = stack.top(); stack.pop();
    
    if (op == '+') stack.push(a + b);
    else if (op == '-') stack.push(a - b);
    else if (op == '*') stack.push(a * b);
    else if (op == '/') {
        if (b == 0)
            throw std::runtime_error("Error");
        stack.push(a / b);
    }
}

int RPN::calculate(const std::string& expression) {
    std::stack<int> stack;
    std::istringstream iss(expression);
    std::string token;
    
    while (iss >> token) {
        if (isOperator(token)) {
            applyOperator(stack, token[0]);
        } else if (isNumber(token)) {
            stack.push(token[0] - '0');
        } else {
            throw std::runtime_error("Error");
        }
    }
    
    if (stack.size() != 1)
        throw std::runtime_error("Error");
    
    return stack.top();
}
