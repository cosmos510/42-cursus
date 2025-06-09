/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:22:04 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/06 11:42:20 by maximemarti      ###   ########.fr       */
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
		Zombie();
		void setName(std::string name);
		~Zombie();
};

Zombie* newZombie(std::string name);
void	randomChump(std::string name);
Zombie* zombieHorde(int N, std::string name );

#endif