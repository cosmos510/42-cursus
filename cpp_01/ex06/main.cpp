/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 19:05:50 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/06 19:06:28 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main(int ac , char **av)
{
	if (ac != 2)
	{
		std::cout << "Wrong number of arguments" << std::endl;
		return 1;
	}
	std::string strarg(av[1]);
	Harl harl;
	harl.complain(strarg);
}