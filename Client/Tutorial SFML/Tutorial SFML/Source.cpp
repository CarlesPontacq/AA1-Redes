#include <SFML/Network.hpp>
#include <iostream>
#include <string>

#define SERVER_PORT 55000
const sf::IpAddress SERVER_IP = sf::IpAddress(127, 0, 0, 1);

enum tipoPaquete { HANDSHAKE, LOGIN, MOVIMIENTO };

sf::Packet& operator>>(sf::Packet& packet, tipoPaquete& tipo) {
	int temp;
	packet >> temp;
	tipo = static_cast<tipoPaquete>(temp);

	return packet;
}

void Handshake(sf::Packet data) {
	std::string receiveMessage;
	data >> receiveMessage;

	std::cout << "Mensaje enviado del servidor: " << receiveMessage << std::endl;
}

void Login(sf::Packet data) {
	std::string user;
	std::string pass;
	data >> user;
	data >> pass;

	std::cout << "El usuario es: " << user << " con la password: " << pass << std::endl;
}


void main()
{
	sf::TcpSocket socket;

	if (socket.connect(SERVER_IP, SERVER_PORT) != sf::Socket::Status::Done) {
		std::cerr << "Error al conectar con el servidor" << std::endl;
	}
	else {
		std::cout << "Conectado al servidor" << std::endl;
		socket.setBlocking(false);
		sf::Packet packet;

		bool gameOver = false;

		while (!gameOver) {
			if (socket.receive(packet) == sf::Socket::Status::Done) {
				tipoPaquete tipo;
				packet >> tipo;

				switch (tipo) {
				case HANDSHAKE:
					Handshake(packet);
					break;
				case LOGIN:
					Login(packet);
					break;
				case MOVIMIENTO:
					break;
				}

				packet.clear();
			}
			if (socket.receive(packet) == sf::Socket::Status::Disconnected) {
				gameOver = true;
			}

			std::string message;
			std::cout << "Inserta mensaje para el servidor, -1 para salir" << std::endl;
			std::cin >> message;

			if (message == "-1") {
				std::cout << "Desconectado..." << std::endl;
				gameOver = true;
			}
			else {
				sf::Packet packet;
				packet << message;
				if (socket.send(packet) != sf::Socket::Status::Done) {
					std::cerr << "Error al enviar el paquete al servidor" << std::endl;
				}
				else {
					std::cout << "Mensaje enviado: " << message << std::endl;
				}
			}
		}

		std::cout << "Desconectado" << std::endl;

	}
}