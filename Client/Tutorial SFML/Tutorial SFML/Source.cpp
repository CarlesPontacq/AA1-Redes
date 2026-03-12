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

	std::cout << "Mensaje Handshake enviado del servidor: " << receiveMessage << std::endl;
}

void Login(sf::Packet data) {
	std::string receiveMessage;
	data >> receiveMessage;

	std::cout << "Mensaje Login enviado del servidor: " << receiveMessage << std::endl;
}


void main()
{
	sf::TcpSocket socket;

	if (socket.connect(SERVER_IP, SERVER_PORT) != sf::Socket::Status::Done) {
		std::cerr << "Error al conectar con el servidor" << std::endl;
	}
	else {
		std::cout << "Conectado al servidor" << std::endl;

		sf::Packet packet;


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
		else {
			std::cerr << "Error al recibir el mensaje del servidor" << std::endl;
		}
	}
}