#pragma once
#include <SFML/Network.hpp>
#include <string>

#define SPTM ServerPacketTypesManager::Instance()

enum PacketTypes
{
	HANDSHAKE, LOGIN, REGISTER, LOOBY_CREATE, LOBBY_JOIN, RANKING, START_GAME, END_GAME
};

class ServerPacketTypesManager
{
public:
	static ServerPacketTypesManager* Instance() {
		static ServerPacketTypesManager ptm;

		return &ptm;
	}

private:
	std::string handshakeMessage = "Handshake realizado";

public:
	void ReceivePacket(sf::Packet packet);
	void SendHandshake(sf::TcpSocket& client);

private:
	ServerPacketTypesManager() = default;
	ServerPacketTypesManager(const ServerPacketTypesManager& ptm) = delete;
	ServerPacketTypesManager& operator=(const ServerPacketTypesManager& ptm) = delete;
	~ServerPacketTypesManager() = default;

	void SedData(sf::TcpSocket& client, sf::Packet& packet);

	void ReceiveHandshakePacket(sf::Packet data);
	void ReceiveLoginPacket(sf::Packet data);
	void ReceiveRegisterPacket(sf::Packet data);
	void ReceiveLobbyCreatePacket(sf::Packet data);
	void ReceiveLobbyJoinPacket(sf::Packet data);
	void ReceiveRankingPacket(sf::Packet data);
	void ReceiveStartGamePacket(sf::Packet data);
	void ReceiveEndGamePacket(sf::Packet data);
};