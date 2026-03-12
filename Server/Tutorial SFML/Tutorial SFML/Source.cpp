#include <SFML/Network.hpp>
#include <iostream>
#include <string>

#define LISTENER_PORT 55000

void SendData(sf::TcpSocket& client, sf::Packet& packet) {
    if (client.send(packet) == sf::Socket::Status::Done) {
        std::cout << "Mensaje enviado" << std::endl;
    }
    else{
        std::cerr << "Error al enviar el mensaje" << std::endl;
    }
}

void main()
{
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
            std::srand(static_cast<unsigned>(std::time(0)));
            int random_value = std::rand() % 2;

            if (random_value == tipoPaquete::HANDSHAKE) {
                std::string message = "Hola cliente";
                packet << tipoPaquete::HANDSHAKE << message;
                SendData(client, packet);
            }
            if (random_value == tipoPaquete::LOGIN) {
                std::string user = "Richard";
                std::string password = "123";
                packet << tipoPaquete::LOGIN << user << password;
                SendData(client, packet);
            }

            packet.clear();
        }
        else {
            std::cerr << "Error al aceptar la conexion" << std::endl;
        }

        client.disconnect();
        closeServer = true;
    }
}