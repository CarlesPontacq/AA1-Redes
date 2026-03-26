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

	void Init();
	void EstablishConnectionWithClient();
	void ReceiveAllClientPacket();
	void CheckForDisconnection();
	
	inline void CloseServer() { closeServer = true; }
	inline bool GetCloseServer() { return closeServer; }
	inline bool CheckIfSocketsAreReadyToReceive() { return selector.wait(); }
private:
	bool closeServer;
	sf::TcpListener listener;
	sf::SocketSelector selector;

	std::vector <sf::TcpSocket*> clients;
	sf::TcpSocket* newClient;

	NetworkManager() = default;
	NetworkManager(const NetworkManager& nt) = delete;
	NetworkManager& operator=(const NetworkManager& nt) = delete;
	~NetworkManager() = default;
};

