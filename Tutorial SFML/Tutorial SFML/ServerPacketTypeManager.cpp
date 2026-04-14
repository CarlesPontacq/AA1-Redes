#include "ServerPacketTypeManager.h"
#include <iostream>

sf::Packet& operator>>(sf::Packet& packet, PacketTypes& tipo) {
	int temp;
	packet >> temp;
	tipo = static_cast<PacketTypes>(temp);

	return packet;
}

sf::Packet& operator<<(sf::Packet& packet, PacketTypes& tipo) {
	int temp;
	temp = static_cast<int>(tipo);
	packet << temp;

	return packet;
}

void ServerPacketTypesManager::ReceivePacket(sf::Packet packet)
{
	PacketTypes packetType;

	packet >> packetType;

	switch (packetType)
	{
	case PacketTypes::HANDSHAKE:
		ReceiveHandshakePacket(packet);
		break;
	case PacketTypes::LOGIN:
		ReceiveLoginPacket(packet);
		break;
	case PacketTypes::REGISTER:
		ReceiveRegisterPacket(packet);
		break;
	case PacketTypes::LOOBY_CREATE:
		ReceiveLobbyCreatePacket(packet);
		break;
	case PacketTypes::LOBBY_JOIN:
		ReceiveLobbyJoinPacket(packet);
		break;
	case PacketTypes::RANKING:
		ReceiveRankingPacket(packet);
		break;
	case PacketTypes::START_GAME:
		ReceiveStartGamePacket(packet);
		break;
	case PacketTypes::END_GAME:
		ReceiveEndGamePacket(packet);
		break;
	default:
		std::cout << "No se ha identificado el tipo de packete" << std::endl;
		break;
	}

	packet.clear();
}

void ServerPacketTypesManager::SedData(sf::TcpSocket& client, sf::Packet& packet)
{
	if (client.send(packet) == sf::Socket::Status::Done) {
		std::cout << "Mensaje enviado" << std::endl;
	}
	else {
		std::cerr << "Error al enviar el mensaje" << std::endl;
	}
}

void ServerPacketTypesManager::SendHandshake(sf::TcpSocket& client)
{
	sf::Packet packet;
	packet << PacketTypes::HANDSHAKE << handshakeMessage;

	std::cout << handshakeMessage << std::endl;

	SedData(client, packet);
}

void ServerPacketTypesManager::ReceiveHandshakePacket(sf::Packet data)
{
	std::string receiveMesage;
	data >> receiveMesage;

	std::cout << "Mensaje enviado del cliente: " << receiveMesage << std::endl;
}

void ServerPacketTypesManager::ReceiveLoginPacket(sf::Packet data)
{
	std::string loginUsername;
	std::string loginPassword;

	data >> loginUsername;
	data >> loginUsername;

	//Desencripta

	bool correctLogin = false;

	//Funcion para comprobar si el login es correcto segun la base de datos (Que devuelva un booleano)

	if (correctLogin) {
		std::cout << "Login correcto de: " << loginUsername << ", pasando a la siguiente escena" << std::endl;
		//Pasar a la siguiente escena
	}
	else {
		std::cout << "Login incorrecto, la contraseya o el usuario están mal" << std::endl;
	}
}

void ServerPacketTypesManager::ReceiveRegisterPacket(sf::Packet data)
{
	std::string registerUsername;
	std::string registerPassword;

	data >> registerUsername;
	data >> registerPassword;

	//Desencripta

	bool correctRegister = false;

	//Funcion para comprobar si el registro es correcto, y si lo es que lo ejecute (Que devuelva un booleano)

	if (correctRegister) {
		std::cout << "Registro completado exitosamente" << std::endl;
		//Pasar a la siguiente escena
	}
	else {
		std::cout << "Registro incorrecto, la contraseya o el usuario no cumplen los requisistos" << std::endl;
	}
}

void ServerPacketTypesManager::ReceiveLobbyCreatePacket(sf::Packet data)
{
	std::string lobbyID;

	data >> lobbyID;

	bool lobbyIDIsAvailable = false;

	//Funcion para comprobar si el ID esta disponible
	 
	if (lobbyIDIsAvailable) {
		//Añadir el jugador en el lobby
		std::cout << "Lobby creado exitosamente, pasando a la sala de espera" << std::endl;
		//Pasar a la siguiente escena o espera
	}
	else {
		std::cout << "El ID " << lobbyID << " no esta disponible ahora mismo, prueba uno diferente" << std::endl;
	}
}

void ServerPacketTypesManager::ReceiveLobbyJoinPacket(sf::Packet data)
{
	std::string lobbyID;

	data >> lobbyID;

	bool lobbyIsAvailable = false;

	//Funcion para comprobar si la sala existe o si esta vacia

	if (lobbyIsAvailable) {
		//Añadir el jugador en el lobby
		std::cout << "Te has unido al lobby exitosamente" << std::endl;
		//Pasar a la siguiente escena o espera
	}
	else {
		std::cout << "El lobby " << lobbyID << " esta lleno o no existe" << std::endl;
	}
}
