/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:28:22 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/05 15:07:00 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(int argc, char **argv)
{
	if (argc == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	else
	{
		for (int i = 1; i < argc; ++i)
		{
			std::string arg = argv[i];
			for (std::size_t j = 0; j < arg.length(); ++j)
				std::cout << static_cast<char>(std::toupper(static_cast<unsigned char>(arg[j])));
		}
	}
	std::cout << std::endl;
	return 0;
}