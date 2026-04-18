#include "ServerPacketTypesManager.h"

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
		std::cout << "No se ha identificado el tipo de paquete" << std::endl;
		break;
	}

	packet.clear();
}

void ServerPacketTypesManager::SendData(sf::TcpSocket& socket, sf::Packet& packet)
{
	if (socket.send(packet) == sf::Socket::Status::Done) {
		std::cout << "Enviando paquete..." << std::endl;
	}
	else {
		std::cerr << "Error al enviar el paquete" << std::endl;
	}
}

void ServerPacketTypesManager::SendHandshake(sf::TcpSocket& server)
{
	sf::Packet packet;
	packet << PacketTypes::HANDSHAKE << handshakeMessage;
	SendData(server, packet);
}

void ServerPacketTypesManager::SendLoginAttempt(std::string username, std::string password, sf::TcpSocket& server)
{
	sf::Packet packet;
	packet << PacketTypes::LOGIN;
	packet << username;
	packet << password;
	SendData(server, packet);
}

void ServerPacketTypesManager::SendRegisterAttempt(std::string username, std::string password, sf::TcpSocket& server)
{
	sf::Packet packet;
	packet << PacketTypes::REGISTER;
	packet << username;
	packet << password;
	SendData(server, packet);
}

void ServerPacketTypesManager::ReceiveHandshakePacket(sf::Packet data)
{
	std::string receiveMesage;
	data >> receiveMesage;
	std::cout << "Mensaje enviado del servidor: " << receiveMesage << std::endl;
}

void ServerPacketTypesManager::ReceiveLoginPacket(sf::Packet data)
{
	bool success;
	std::string username;

	data >> success;
	data >> username;

	if (success) {
		std::cout << "Login correcto! Bienvenido " << username << std::endl;
	}
	else {
		std::cout << "Login incorrecto" << std::endl;
	}
}

void ServerPacketTypesManager::ReceiveRegisterPacket(sf::Packet data)
{
	bool success;
	std::string username;

	data >> success;
	data >> username;

	if (success) {
		std::cout << "Registro correcto! Usuario " << username << " creado" << std::endl;
	}
	else {
		std::cout << "Registro fallido " << std::endl;
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

void ServerPacketTypesManager::ReceiveRankingPacket(sf::Packet data)
{
}

void ServerPacketTypesManager::ReceiveStartGamePacket(sf::Packet data)
{
}

void ServerPacketTypesManager::ReceiveEndGamePacket(sf::Packet data)
{
}
