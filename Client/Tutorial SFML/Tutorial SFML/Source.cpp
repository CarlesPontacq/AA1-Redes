#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include "ServerPacketTypesManager.h"

#define SERVER_PORT 55000
const sf::IpAddress SERVER_IP = sf::IpAddress(127, 0, 0, 1);

void main()
{
	sf::TcpSocket socket;

	if (socket.connect(SERVER_IP, SERVER_PORT) != sf::Socket::Status::Done) {
		std::cerr << "Error al conectar con el servidor" << std::endl;
	}
	else {
		std::cout << "Conectado al servidor" << std::endl;
		socket.setBlocking(false);
		bool gameOver = false;

		SPTM->SendHandshake(socket);

		while (!gameOver) {
			sf::Packet receivePacket;

			if (socket.receive(receivePacket) == sf::Socket::Status::Done) {
				SPTM->ReceivePacket(receivePacket);
			}

			if (socket.receive(receivePacket) == sf::Socket::Status::Disconnected) {
				gameOver = true;
			}

			std::cout << "\n=== MENU ===" << std::endl;
			std::cout << "1. Login" << std::endl;
			std::cout << "2. Register" << std::endl;
			std::cout << "3. Salir" << std::endl;
			std::cout << "Opcion: ";

			int opcion;
			std::cin >> opcion;

			if (opcion == 1) {
				// LOGIN
				std::string username, password;
				std::cout << "Usuario: ";
				std::cin >> username;
				std::cout << "Contrasenya: ";
				std::cin >> password;

				SPTM->SendLoginAttempt(username, password, socket);
			}
			else if (opcion == 2) {
				// REGISTER
				std::string username, password;
				std::cout << "Nuevo usuario: ";
				std::cin >> username;
				std::cout << "Contrasenya : ";
				std::cin >> password;

				SPTM->SendRegisterAttempt(username, password, socket);
			}
			else if (opcion == 3) {
				std::cout << "Desconectando..." << std::endl;
				gameOver = true;
			}

			sf::sleep(sf::milliseconds(100));
		}

		std::cout << "Desconectado" << std::endl;

	}
}