#include "NetworkManager.h"

void NetworkManager::Init()
{
    if (listener.listen(LISTENER_PORT) != sf::Socket::Status::Done) {
        std::cerr << "Error al iniciar el servidor" << std::endl;
        closeServer = true;
    }

    selector.add(listener);
}

void NetworkManager::ReceiveClient()
{
    if (selector.isReady(listener)) {
        newClient = new sf::TcpSocket();

        if (listener.accept(*newClient) == sf::Socket::Status::Done) {
            newClient->setBlocking(false);
            selector.add(*newClient);

            //Hacer Handshake

            //Se crearia aqui el cliente con su clase Cliente

            clients.push_back(newClient);
            std::cout << "Nueva conexion establecida" << std::endl;
        }
    }
}
