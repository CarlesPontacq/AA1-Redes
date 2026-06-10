#include "NetworkManager.h"

void NetworkManager::Init()
{
    closeServer = false;

    if (listener.listen(LISTENER_PORT) != sf::Socket::Status::Done) {
        std::cerr << "Error al iniciar el servidor" << std::endl;
        closeServer = true;
    }

    selector.add(listener);
    std::cout << "Servidor Abierto" << std::endl;
}

void NetworkManager::Update()
{
    EstablishConnectionWithClient();
    ReceiveClientPacket();
    CheckForDisconnection();
}

void NetworkManager::EstablishConnectionWithClient()
{
    if (selector.isReady(listener)) {
        newClient = new sf::TcpSocket();

        if (listener.accept(*newClient) == sf::Socket::Status::Done) {
            newClient->setBlocking(false);
            
            SPTM->SendHandshake(*newClient);
            selector.add(*newClient);

            clients.push_back(newClient);

			User newUser;
			clientsMap.insert({ newClient, newUser });

            std::cout << "Nueva conexion establecida" << std::endl;
        }
    }
}

void NetworkManager::ReceiveClientPacket()
{
    if (!selector.isReady(listener)) {
        for (int i = 0; i < clients.size(); i++) {
            if (selector.isReady(*clients[i])) {
                sf::Packet packet;

                if (clients[i]->receive(packet) == sf::Socket::Status::Done) {
                    SPTM->ReceivePacket(packet, *clients[i]);
                }
            }
        }
    }
}

void NetworkManager::CheckForDisconnection()
{
    if (!selector.isReady(listener)) {
        for (int i = 0; i < clients.size(); i++) {
            if (selector.isReady(*clients[i])) {
                sf::Packet packet;

                if (clients[i]->receive(packet) == sf::Socket::Status::Disconnected) {
					clientsMap.erase(clients[i]);

                    selector.remove(*clients[i]);

                    delete clients[i];
                    clients.erase(clients.begin() + i);
                    i--;

                    std::cout << "Cliente desconectado" << std::endl;
                }
            }
        }
    }
}

void NetworkManager::SetNewCorrectUser(sf::TcpSocket* client, std::string username, int points)
{
    if (clientsMap.find(client) != clientsMap.end()) {
		clientsMap[client].nickname = username;
		clientsMap[client].score = points;
        std::cout << "Cambiando el usuario " << clientsMap[client].nickname << " por : " << username << std::endl;
    }
}

bool NetworkManager::CheckIfNewUserExists(sf::TcpSocket* client, std::string username)
{
	bool userExists = false;

    for(auto& pair : clientsMap) {
        if (pair.second.nickname == username) {
	        std::cout << "Verificando si el usuario " << username << " es el siguiente usuario: " << clientsMap[client].nickname << std::endl;
            userExists = true;
            break;
        }
	}

    return userExists;
}
