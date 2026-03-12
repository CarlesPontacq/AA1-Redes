#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <time.h>

#define LISTENER_PORT 55000

void main()
{
    srand(time(NULL));

    enum tipoPaquete {HANDSHAKE, LOGIN, MOVIMIENTO};

    sf::TcpListener listener;
    sf::TcpSocket client;

    bool closeServer = false;

    //listener.setBlocking(false);

    if (listener.listen(LISTENER_PORT) != sf::Socket::Status::Done) {
        std::cerr << "Error al intentar escuchar en el puerto " << LISTENER_PORT << std::endl;
    }

    while (!closeServer) {
        std::cout << "Esperando conexion..." << std::endl;
        if (listener.accept(client) == sf::Socket::Status::Done) {
            std::cout << "Cliente conectado desde " << client.getRemoteAddress().value() << std::endl;

            sf::Packet packet;
            std::string message = "Hola cliente";

            int tempRandom = rand() % 2;

            switch (tempRandom)
            {
            case 0:
                packet << tipoPaquete::HANDSHAKE << message;
                break;
            case 1:
                packet << tipoPaquete::LOGIN << message;
                break;
            }


            if (client.send(packet) == sf::Socket::Status::Done) {
                std::cout << "Mensaje enviado: " << message << std::endl;
                packet.clear();
            }
            else {
                std::cerr << "Error al enviar el mensaje al cliente" << std::endl;
            }
        }
        else {
            std::cerr << "Error al aceptar la conexion" << std::endl;
        }

    }

}