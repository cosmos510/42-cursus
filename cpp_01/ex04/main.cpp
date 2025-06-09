/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:28:26 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/06 18:13:44 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <fstream>

void replaceInFile(const std::string& filename, std::string& search, std::string& replace)
{
	std::ifstream file(filename);
	if (!file)
	{
		std::cout << "Error opening: " << filename << std::endl;
		return ;
	}
	std::ofstream outFile(filename + ".replace");
	if (!outFile)
	{
		std::cout << "Error opening: " << outFile << std::endl;
		return ;
	}
	std::string line;
	while (std::getline(file, line))
	{
		size_t pos = 0;
		while ((pos = line.find(search, pos)) != std::string::npos)
		{
			line.erase(pos, search.length());
			line.insert(pos, replace);
			pos += replace.length();
		}
		outFile << line << std::endl;
	}
	file.close();
	outFile.close();
	
}

int main(int ac, char **av)
{
	if (ac != 4)
	{
		std::cout << "Usage ./ex04 <filename> <string to search> <replace string>" << std::endl;
		return 1;
	}
	std::string filename = av[1];
	if (filename.empty())
	{
		std::cout << "Error: filename, cannot be empty." << std::endl;
		return 1;
	}
	std::string search = av[2];
	std::string replace = av[3];
	replaceInFile(filename, search, replace);
}