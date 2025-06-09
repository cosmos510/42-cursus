/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:17:51 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/05 16:56:41 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "PhoneBook.hpp"

int main() {
	PhoneBook phoneBook;
	std::string command;

	while (true)
	{
		std::cout << "Enter a command (ADD, SEARCH, EXIT): ";
		std::getline(std::cin, command);

		if (std::cin.eof())
		{
			std::cout << "\nEOF detected. Exiting.\n";
			break;
		}
		if (!command.compare("ADD"))
			phoneBook.addContact();
		else if (!command.compare("SEARCH"))
			phoneBook.searchContacts();
		else if (!command.compare("EXIT"))
			break;
	}
	std::cout << "Goodbye!\n";
	return 0;
}