#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include "ServerPacketTypesManager.h"

#define NT NetworkManager::Instance()
#define SERVER_PORT 55000
const sf::IpAddress SERVER_IP = sf::IpAddress(127, 0, 0, 1);

class NetworkManager
{
public:
	static NetworkManager* Instance() {
		static NetworkManager nt;

		return &nt;
	}

private:
	bool disconnectFromServer;
	sf::TcpSocket socket;

public:
	void Init();
	void Update();

	inline void DisconnectFromServer() { disconnectFromServer = true; }
	inline bool GetDisconnectFromServer() { return disconnectFromServer; }
	sf::TcpSocket* GetServerSocket();

private:
	NetworkManager() = default;
	NetworkManager(const NetworkManager& nt) = delete;
	NetworkManager& operator=(const NetworkManager& nt) = delete;
	~NetworkManager() = default;

	void EstablishConnectionWithServer();
	void HandleReceivedPackets();
	void SendServerPacket();
};

