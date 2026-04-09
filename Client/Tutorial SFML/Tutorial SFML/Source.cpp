#include <SFML/Network.hpp>
#include <iostream>
#include <string>

#define SERVER_PORT 55000
const sf::IpAddress SERVER_IP = sf::IpAddress(127, 0, 0, 1);

enum PacketTypes
{
	HANDSHAKE, LOGIN, REGISTER, LOOBY_CREATE, LOBBY_JOIN, RANKING, START_GAME, END_GAME
};

sf::Packet& operator>>(sf::Packet& packet, PacketTypes& tipo) {
	int temp;
	packet >> temp;
	tipo = static_cast<PacketTypes>(temp);

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
		bool gameOver = false;

		while (!gameOver) {
			sf::Packet receivePacket;

			if (socket.receive(receivePacket) == sf::Socket::Status::Done) {
				PacketTypes tipo;
				receivePacket >> tipo;

				switch (tipo) {
				case HANDSHAKE:
					Handshake(receivePacket);
					break;
				case LOGIN:
					Login(receivePacket);
					break;
				default:
					std::cout << "No detectado tipo de paquete" << std::endl;
					break;
				}

				receivePacket.clear();
			}
			if (socket.receive(receivePacket) == sf::Socket::Status::Disconnected) {
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
				sf::Packet sendPacket;
				sendPacket << message;
				if (socket.send(sendPacket) != sf::Socket::Status::Done) {
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