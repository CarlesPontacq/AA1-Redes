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

void LoginResponse(sf::Packet data) {
	bool success;
	std::string username;
	std::string message;

	data >> success;
	data >> username;
	data >> message;

	if (success) {
		std::cout << "Login correcto! Bienvenido " << username << std::endl;
		std::cout << "Mensaje del servidor: " << message << std::endl;
	}
	else {
		std::cout << "Login incorrecto" << message << std::endl;
	}
}

void RegisterResponse(sf::Packet data) {
	bool success;
	std::string username;
	std::string message;

	data >> success;
	data >> username;
	data >> message;

	if (success) {
		std::cout << "Registro correcto! Usuario " << username << " creado" << std::endl;
		std::cout << "Mensaje del servidor: " << message << std::endl;
	}
	else {
		std::cout << "Registro fallido " << message << std::endl;
	}
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
					LoginResponse(receivePacket);
					break;
				case REGISTER:
					RegisterResponse(receivePacket);
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

				sf::Packet packet;
				packet << PacketTypes::LOGIN;
				packet << username;
				packet << password;

				if (socket.send(packet) == sf::Socket::Status::Done) {
					std::cout << "Enviando solicitud de login..." << std::endl;
				}
				else {
					std::cerr << "Error al enviar login" << std::endl;
				}
			}
			else if (opcion == 2) {
				// REGISTER
				std::string username, password;
				std::cout << "Nuevo usuario: ";
				std::cin >> username;
				std::cout << "Contrasenya : ";
				std::cin >> password;

				sf::Packet packet;
				packet << PacketTypes::REGISTER;
				packet << username;
				packet << password;

				if (socket.send(packet) == sf::Socket::Status::Done) {
					std::cout << "Enviando solicitud de registro..." << std::endl;
				}
				else {
					std::cerr << "Error al enviar registro" << std::endl;
				}
			}
			else if (opcion == 3) {
				std::cout << "Desconectando..." << std::endl;
				gameOver = true;
			}

			// Pequeña pausa para recibir respuesta
			sf::sleep(sf::milliseconds(100));
		}

		std::cout << "Desconectado" << std::endl;

	}
}