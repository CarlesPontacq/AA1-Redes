#include <SFML/Network.hpp>
#include <iostream>
#include "NetworkManager.h"

#define LISTENER_PORT 55000

void SendData(sf::TcpSocket& client, sf::Packet& packet) {
    if (client.send(packet) == sf::Socket::Status::Done) {
        std::cout << "Mensaje enviado" << std::endl;
    }
    else {
        std::cerr << "Error al enviar el mensaje" << std::endl;
    }
}



void main()
{

    NT->Init();

    while (!NT->closeServer) {
        if (NT->selector.wait()) {
            NT->ReceiveClient();

            if (!NT->selector.isReady(NT->listener)) {
                for (int i = 0; i < NT->clients.size(); i++) {
                    if (NT->selector.isReady(*NT->clients[i])) {
                        sf::Packet packet;

                        if (NT->clients[i]->receive(packet) == sf::Socket::Status::Done) {
                            std::string message;
                            packet >> message;

                            std::cout << "Mensaje: " << message << std::endl;
                        }

                        if (NT->clients[i]->receive(packet) == sf::Socket::Status::Disconnected) {
                            NT->selector.remove(*NT->clients[i]);
                            delete NT->clients[i];
                            NT->clients.erase(NT->clients.begin() + i);
                            i--;

                            std::cout << "Cliente desconectado" << std::endl;
                        }
                    }
                }
            }
        }
    }
}