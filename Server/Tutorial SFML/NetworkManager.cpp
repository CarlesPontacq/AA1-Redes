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

            unsigned int clientID = GenerateUnusedID();

            clients.emplace(clientID, *newClient);
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
                    selector.remove(*clients[i]);
                    delete clients[i];
                    //clients.erase(clients.begin() + i);
                    i--;

                    std::cout << "Cliente desconectado" << std::endl;
                }
            }
        }
    }
}

unsigned int NetworkManager::GenerateUnusedID()
{
    unsigned int newID = rand();

    if (clients.find(newID) != clients.end()) {
        newID = GenerateUnusedID();
    }

    std::cout << "New Client ID: " << newID << std::endl;

    return newID;
}

unsigned int NetworkManager::CheckIfIDExists(int IDToCheck)
{


    return 0;
}

