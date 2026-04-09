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
		break;
	case PacketTypes::REGISTER:
		break;
	case PacketTypes::LOOBY_CREATE:
		break;
	case PacketTypes::LOBBY_JOIN:
		break;
	case PacketTypes::RANKING:
		break;
	case PacketTypes::START_GAME:
		break;
	case PacketTypes::END_GAME:
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