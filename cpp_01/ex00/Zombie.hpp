/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:33:56 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/06 11:05:59 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP
#include <iostream>

class Zombie
{
	private:
		std::string _name;
	public:
		Zombie(std::string name);
		void announce();
		~Zombie();
};

Zombie* newZombie(std::string name);
void	randomChump(std::string name);
#endif