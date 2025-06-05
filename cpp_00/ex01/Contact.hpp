/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:25:01 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/05 17:32:21 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

#include <iostream>

class Contact
{
	private:
		std::string first_name;
		std::string last_name;
		std::string nickname;
		std::string phone_number;
		std::string darkest_secret;

	public:
		void displayContact() const;
		bool isEmpty() const;

		// Setters
		void setFirstName(const std::string& first_name);
		void setLastName(const std::string& last_name);
		void setNickname(const std::string& nickname);
		void setPhoneNumber(const std::string& phone_number);
		void setDarkestSecret(const std::string& darkest_secret);

		// Getters
		std::string getFirstName() const;
		std::string getLastName() const;
		std::string getNickname() const;
		std::string getPhoneNumber() const;
		std::string getDarkestSecret() const;
};

#endif