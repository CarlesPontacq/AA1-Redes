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

void ServerPacketTypesManager::ReceivePacket(sf::Packet packet, sf::TcpSocket& client)
{
	PacketTypes packetType;

	packet >> packetType;

	switch (packetType)
	{
	case PacketTypes::HANDSHAKE:
		ReceiveHandshakePacket(packet);
		break;
	case PacketTypes::LOGIN:
		ReceiveLoginPacket(packet, client);
		break;
	case PacketTypes::REGISTER:
		ReceiveRegisterPacket(packet, client);
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

void ServerPacketTypesManager::SendData(sf::TcpSocket& client, sf::Packet& packet)
{
	if (client.send(packet) == sf::Socket::Status::Done) {
		std::cout << "Enviando paquete..." << std::endl;
	}
	else {
		std::cerr << "Error al enviar el paquete" << std::endl;
	}
}

void ServerPacketTypesManager::SendHandshake(sf::TcpSocket& client)
{
	sf::Packet packet;
	packet << PacketTypes::HANDSHAKE << handshakeMessage;
	SendData(client, packet);
}

void ServerPacketTypesManager::SendLoginResponse(sf::TcpSocket& client, bool success, const std::string& username)
{
	sf::Packet packet;
	packet << PacketTypes::LOGIN;
	packet << success;
	packet << username;

	SendData(client, packet);

	std::cout << "Respuesta de login enviada" << std::endl;
}

void ServerPacketTypesManager::SendRegisterResponse(sf::TcpSocket& client, bool success, const std::string& username)
{
	sf::Packet packet;
	packet << PacketTypes::REGISTER;
	packet << success;
	packet << username;

	SendData(client, packet);

	std::cout << "Respuesta de registro enviada" << std::endl;
}

void ServerPacketTypesManager::ReceiveHandshakePacket(sf::Packet data)
{
	std::string receiveMesage;
	data >> receiveMesage;

	std::cout << "Mensaje enviado del cliente: " << receiveMesage << std::endl;
}

void ServerPacketTypesManager::ReceiveLoginPacket(sf::Packet data, sf::TcpSocket& client)
{
	std::string loginUsername;
	std::string loginPassword;

	data >> loginUsername;
	data >> loginPassword;

	int userId = 0;

	bool correctLogin = DB->LoginUser(loginUsername, loginPassword, userId);

	SendLoginResponse(client, correctLogin, loginUsername);

	if (correctLogin) {
		//Pasar a la siguiente escena
	}
}

void ServerPacketTypesManager::ReceiveRegisterPacket(sf::Packet data, sf::TcpSocket& client)
{
	std::string registerUsername;
	std::string registerPassword;

	data >> registerUsername;
	data >> registerPassword;

	std::string passwordHash = bcrypt::generateHash(registerPassword);
	
	bool correctRegister = DB->RegisterUser(registerUsername, passwordHash);

	SendRegisterResponse(client, correctRegister, registerUsername);

	if (correctRegister) {
		//Pasar a la siguiente escena
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
