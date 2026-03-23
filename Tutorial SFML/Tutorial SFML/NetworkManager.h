#pragma once
#include <SFML/Network.hpp>
#include <iostream>

#define NT NetworkManager::Instance()
#define LISTENER_PORT 55000

class NetworkManager
{
	
public:
	static NetworkManager* Instance() {
		static NetworkManager nt;

		return &nt;
	}

	bool closeServer = false;

	sf::TcpListener listener;
	sf::SocketSelector selector;

	std::vector <sf::TcpSocket*> clients;
	sf::TcpSocket* newClient;

	void Init();
	void ReceiveClient();

private:
	NetworkManager();


	NetworkManager(const NetworkManager& nt) = delete;
	NetworkManager& operator=(const NetworkManager& nt) = delete;
	~NetworkManager() = default;
};

