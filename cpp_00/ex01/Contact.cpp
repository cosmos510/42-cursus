/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:43:22 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/05 17:32:47 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

void Contact::displayContact() const {
    std::cout << "First name: " << first_name << std::endl;
    std::cout << "Last name: " << last_name << std::endl;
    std::cout << "Nickname: " << nickname << std::endl;
    std::cout << "Phone number: " << phone_number << std::endl;
    std::cout << "Darkest secret: " << darkest_secret << std::endl;
}

bool Contact::isEmpty() const
{
	return first_name.empty() && last_name.empty() &&
	       nickname.empty() && phone_number.empty() &&
	       darkest_secret.empty();
}

std::string Contact::getFirstName() const
{
    return first_name;
}

std::string Contact::getLastName() const
{
    return last_name;
}

std::string Contact::getNickname() const
{
    return nickname;
}
std::string Contact::getPhoneNumber() const
{
    return phone_number;
}
std::string Contact::getDarkestSecret() const
{
    return darkest_secret;
}

void Contact::setFirstName(const std::string& value)
{
	first_name = value;
}
void Contact::setLastName(const std::string& value)
{
	last_name = value;
}

void Contact::setNickname(const std::string& value)
{
	nickname = value;
}

void Contact::setPhoneNumber(const std::string& value)
{
	phone_number = value;
}

void Contact::setDarkestSecret(const std::string& value)
{
	darkest_secret = value;
}