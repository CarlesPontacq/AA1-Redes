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

    while (!NT->GetCloseServer()) {
        if (NT->CheckIfSocketsAreReadyToReceive()) {
            NT->EstablishConnectionWithClient();
            NT->ReceiveAllClientPacket();
            NT->CheckForDisconnection();

        }
    }
}