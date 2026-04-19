#include "NetworkManager.h"

void NetworkManager::Init() {
    EstablishConnectionWithServer();
}

void NetworkManager::EstablishConnectionWithServer()
{
    disconnectFromServer = false;

    if (socket.connect(SERVER_IP, SERVER_PORT) != sf::Socket::Status::Done) {
        std::cerr << "Error al conectar con el servidor" << std::endl;
        disconnectFromServer = true;
    }
    else {
        socket.setBlocking(false);
        SPTM->SendHandshake(socket);
        HandleReceivedPackets();
        std::cout << "Conectado al servidor" << std::endl;
    }
}

void NetworkManager::Update()
{
    if (!disconnectFromServer) {
        HandleReceivedPackets();
        //SendServerPacket();
    }
}

sf::TcpSocket* NetworkManager::GetServerSocket()
{
    if (!disconnectFromServer)
        return &socket;
    
    return nullptr;
}

void NetworkManager::SendLoginAttemptServerPacket(std::string username, std::string password)
{
    SPTM->SendLoginAttempt(username, password, socket);
}

void NetworkManager::SendRegisterAttemptServerPacket(std::string username, std::string password)
{
    SPTM->SendRegisterAttempt(username, password, socket);
}

void NetworkManager::SendLobbyCreateAttemptPacket(std::string lobbyId)
{
    SPTM->SendLobbyCreateAttempt(lobbyId, socket);
}

void NetworkManager::SendLobbyJoinAttemptPacket(std::string lobbyId)
{
    SPTM->SendLobbyJoinAttempt(lobbyId, socket);
}

void NetworkManager::HandleReceivedPackets()
{
    sf::Packet receivePacket;
    if(socket.receive(receivePacket) == sf::Socket::Status::Done) {
        SPTM->ReceivePacket(receivePacket);
    }
    else if (socket.receive(receivePacket) == sf::Socket::Status::Disconnected) {
        std::cout << "Servidor desconectado" << std::endl;
        disconnectFromServer = true;
    }
}

void NetworkManager::SendServerPacket()
{
    std::cout << "\n=== MENU ===" << std::endl;
    std::cout << "1. Login" << std::endl;
    std::cout << "2. Register" << std::endl;
    std::cout << "3. Salir" << std::endl;
    std::cout << "Opcion: ";

    int opcion;
    std::cin >> opcion;

    if (opcion == 1) {
        // LOGIN
        std::string username, password;
        std::cout << "Usuario: ";
        std::cin >> username;
        std::cout << "Contrasenya: ";
        std::cin >> password;

        SPTM->SendLoginAttempt(username, password, socket);
    }
    else if (opcion == 2) {
        // REGISTER
        std::string username, password;
        std::cout << "Nuevo usuario: ";
        std::cin >> username;
        std::cout << "Contrasenya : ";
        std::cin >> password;

        SPTM->SendRegisterAttempt(username, password, socket);
    }
    else if (opcion == 3) {
        std::cout << "Desconectando..." << std::endl;
        disconnectFromServer = true;
    }
}
