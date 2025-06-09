/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:15:59 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/05 17:29:55 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iomanip>

PhoneBook::PhoneBook() : index(0), size(0) {}


std::string getNonEmptyInput(const std::string& prompt) {
	std::string input;
	do {
		std::cout << prompt;
		if (!std::getline(std::cin, input)) {
			std::cout << "\nEOF detected. Aborting.\n";
			exit(0);
		}
		if (input.empty())
			std::cout << "Field cannot be empty. Please enter again." << std::endl;
	} while (input.empty());
	return input;
}

std::string getValidPhoneNumber(const std::string& prompt) {
	std::string input;
	bool valid;

	do {
		std::cout << prompt;
		if (!std::getline(std::cin, input)) {
			std::cout << "\nEOF detected. Aborting.\n";
			exit(0);
		}
		valid = !input.empty();
		for (size_t i = 0; i < input.size() && valid; ++i) {
			if (!isdigit(input[i])) {
				valid = false;
			}
		}

		if (!valid)
			std::cout << "Please enter a valid phone number (digits only)." << std::endl;

	} while (!valid);

	return input;
}

void PhoneBook::displayHeader() const {
    std::cout << std::setw(10) << "Index" << "|"
              << std::setw(10) << "First Name" << "|"
              << std::setw(10) << "Last Name" << "|"
              << std::setw(10) << "Nickname" << std::endl;
}

static std::string formatField(const std::string& str) {
	if (str.length() > 10)
		return str.substr(0, 9) + ".";
	return std::string(10 - str.length(), ' ') + str;
}

void PhoneBook::searchContacts() const {
	if (size == 0) {
		std::cout << "No contacts found.\n";
		return;
	}

	displayHeader();

	for (int i = 0; i < size; ++i) {
		std::cout << std::setw(10) << i << "|"
		          << formatField(contacts[i].getFirstName()) << "|"
		          << formatField(contacts[i].getLastName()) << "|"
		          << formatField(contacts[i].getNickname()) << std::endl;
	}

	std::string input;
	std::cout << "Enter contact index: ";
	std::getline(std::cin, input);

	if (input.length() != 1 || !isdigit(input[0])) {
		std::cout << "Invalid input.\n";
		return;
	}

	int index = input[0] - '0';
	if (index < 0 || index >= size) {
		std::cout << "Index out of range.\n";
		return;
	}

	contacts[index].displayContact();
}

void PhoneBook::addContact() {
	std::string input;
	Contact newContact;

	newContact.setFirstName(getNonEmptyInput("Enter first name: "));
	newContact.setLastName(getNonEmptyInput("Enter last name: "));
	newContact.setNickname(getNonEmptyInput("Enter nickname: "));
	newContact.setPhoneNumber(getValidPhoneNumber("Enter phone number: "));
	newContact.setDarkestSecret(getNonEmptyInput("Enter darkest secret: "));

	contacts[index] = newContact;

	index = (index + 1) % 8;  // circular buffer
	if (size < 8)
		size++;

	std::cout << "Contact added successfully!\n";
}