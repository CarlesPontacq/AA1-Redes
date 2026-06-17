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
        localPort = socket.getLocalPort();
        SPTM->SendHandshake(socket);
        HandleReceivedPackets();
        std::cout << "Conectado al servidor" << std::endl;
    }
}

void NetworkManager::Update()
{
    if (!disconnectFromServer) {
        HandleReceivedPackets();
    }

    if (establishedP2PConnection) {
        HandleP2PConnections();
    }
}

void NetworkManager::StartP2P()
{
    socket.disconnect();

    if (listener.listen(localPort) != sf::Socket::Status::Done) {
        std::cerr << "Error al iniciar el P2P" << std::endl;
        return;
    }

    selector.add(listener);

    for (const auto& other : clientsInfo) {
        sf::TcpSocket* socket = new sf::TcpSocket();

        std::optional<sf::IpAddress> ipAddress = sf::IpAddress::resolve(other.ip);
        if (socket->connect(ipAddress.value(), other.port, sf::seconds(timeoutTime)) == sf::Socket::Status::Done) {
            std::cout << "Conectado con el usuario: " << other.username << " (" << other.ip << ":" << other.port << ")" << std::endl;
            otherClientsSockets.push_back(socket);
            selector.add(*socket);
        }
        else {
            std::cout << "No se ha podido conectar con el usuario: " << other.username << " ("
                << other.ip << ":" << other.port << ")" << std::endl;
            delete socket;
        }
    } 

    establishedP2PConnection = true;
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

void NetworkManager::SendRankingPetitionServerPacket(int userId)
{
    SPTM->SendRankingPetition(userId, socket);
}

void NetworkManager::SaveClientsInfo(std::string ip, unsigned short port, std::string username)
{
    ClientsConnectionInfo info;
    info.ip = ip;
    info.port = port;
    info.username = username;

    clientsInfo.push_back(info);
}

void NetworkManager::HandleP2PConnections()
{
    if (!selector.isReady(listener)) {
        int iterator = 0;

        for (auto socket : otherClientsSockets) {
            iterator++;
            sf::Packet packet;
            if (socket->receive(packet) == sf::Socket::Status::Done) {
                SPTM->ReceiveP2PPacket(packet);
            }
            else {
                selector.remove(*socket);

                delete socket;
                otherClientsSockets.erase(otherClientsSockets.begin() + iterator);
                iterator--;

                std::cout << "Jugador desconectado" << std::endl;
            }
        }
    }
    else {
        std::cout << "Selector is not ready" << std::endl;
    }
}

void NetworkManager::SendTurnMovePacket(Move move, int currentPlayer)
{
    for (auto socket : otherClientsSockets) {
        SPTM->SendTurnPacket(move, currentPlayer, *socket);
    }
}

void NetworkManager::SendLobbyCreateAttemptPacket(std::string lobbyId)
{
    SPTM->SendLobbyCreateAttempt(lobbyId, socket);
}

void NetworkManager::SendLobbyJoinAttemptPacket(std::string lobbyId)
{
    SPTM->SendLobbyJoinAttempt(lobbyId, socket);
}

void NetworkManager::SendStartGamePacket(std::string lobbyId)
{
	SPTM->SendStartGamePetition(lobbyId, socket);
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