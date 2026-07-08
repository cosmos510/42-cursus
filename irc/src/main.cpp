/* ************************************************************************** */
/*                                                                            */
/*   main.cpp - Point d'entree du serveur IRC                                 */
/*                                                                            */
/*   Usage : ./ircserv <port> <password>                                      */
/*   - port : numero de port TCP sur lequel le serveur ecoute (1-65535)       */
/*   - password : mot de passe que les clients doivent fournir via PASS       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char** argv) {
	// Verification du nombre d'arguments
	if (argc != 3) {
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		return 1;
	}

	// Validation du port : doit etre un entier entre 1 et 65535
	int port = std::atoi(argv[1]);
	if (port <= 0 || port > 65535) {
		std::cerr << "Error: invalid port number" << std::endl;
		return 1;
	}

	// Le mot de passe ne peut pas etre vide
	std::string password = argv[2];
	if (password.empty()) {
		std::cerr << "Error: password cannot be empty" << std::endl;
		return 1;
	}

	// Creation et lancement du serveur
	// Le try/catch attrape les erreurs fatales (socket, bind, listen)
	try {
		Server server(port, password);
		server.run();
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
