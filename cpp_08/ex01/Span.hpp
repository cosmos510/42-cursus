/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 10:30:00 by maximemarti       #+#    #+#             */
/*   Updated: 2026/02/16 10:30:01 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <exception>

class Span {
private:
	unsigned int _maxSize;
	std::vector<int> _numbers;

public:
	Span(unsigned int n);
	Span(const Span& other);
	Span& operator=(const Span& other);
	~Span();

	void addNumber(int number);
	template<typename Iterator>
	void addNumber(Iterator begin, Iterator end);
	int shortestSpan() const;
	int longestSpan() const;

	class FullException : public std::exception {
		virtual const char* what() const throw();
	};

	class NoSpanException : public std::exception {
		virtual const char* what() const throw();
	};
};

template<typename Iterator>
void Span::addNumber(Iterator begin, Iterator end) {
	for (Iterator it = begin; it != end; ++it) {
		if (_numbers.size() >= _maxSize)
			throw FullException();
		_numbers.push_back(*it);
	}
}

#endif
