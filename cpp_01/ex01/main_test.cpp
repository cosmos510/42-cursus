#include "Zombie.hpp"
#include <iostream>
#include <cstdlib> // for std::atoi

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./zombie_horde_test <horde_size>\n";
		return 1;
	}

	int horde_size = std::atoi(argv[1]);
	if (horde_size <= 0)
	{
		std::cerr << "Horde size must be a positive integer.\n";
		return 1;
	}

	Zombie* horde = zombieHorde(horde_size, "zombie horde");

	for (int i = 0; i < horde_size; i++)
		horde[i].announce();

	delete[] horde;
	return 0;
}