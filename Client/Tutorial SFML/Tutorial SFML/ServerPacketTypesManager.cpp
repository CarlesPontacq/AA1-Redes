#include "ServerPacketTypesManager.h"
#include "NetworkManager.h"
#include "LobbyManager.h"
#include "User.h"
#include "SharedMemory.h"

sf::Packet& operator>>(sf::Packet& packet, PacketTypes& tipo) {
	int temp;
	packet >> temp;
	tipo = static_cast<PacketTypes>(temp);

	return packet;
}

sf::Packet& operator<<(sf::Packet& packet, PacketTypes& tipo) {
	int temp;
	temp = static_cast<int>(tipo);
	packet << temp;

	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, P2PPacketTypes& tipo) {
	int temp;
	packet >> temp;
	tipo = static_cast<P2PPacketTypes>(temp);

	return packet;
}

sf::Packet& operator<<(sf::Packet& packet, P2PPacketTypes& tipo) {
	int temp;
	temp = static_cast<int>(tipo);
	packet << temp;

	return packet;
}

void ServerPacketTypesManager::ReceiveP2PPacket(sf::Packet packet)
{
	P2PPacketTypes packetType;

	packet >> packetType;

	switch (packetType)
	{
	case P2PPacketTypes::TURN_ACTION:
		ReceiveP2PTurnActionPacket(packet);
		break;
	case P2PPacketTypes::GAME_OVER:
		ReceiveP2PEndGamePacket(packet);
		break;
	default:
		std::cout << "No se ha identificado el tipo de paquete P2P" << std::endl;
		break;
	}

	packet.clear();
}

void ServerPacketTypesManager::ReceivePacket(sf::Packet packet)
{
	PacketTypes packetType;

	packet >> packetType;

	switch (packetType)
	{
	case PacketTypes::HANDSHAKE:
		ReceiveHandshakePacket(packet);
		break;
	case PacketTypes::LOGIN:
		ReceiveLoginPacket(packet);
		break;
	case PacketTypes::REGISTER:
		ReceiveRegisterPacket(packet);
		break;
	case PacketTypes::LOBBY_CREATE:
		ReceiveLobbyCreatePacket(packet);
		break;
	case PacketTypes::LOBBY_JOIN:
		ReceiveLobbyJoinPacket(packet);
		break;
	case PacketTypes::WAITING_ROOM_PLAYERS:
		ReceivePlayerCountPacket(packet);
		break;
	case PacketTypes::RANKING:
		ReceiveRankingPacket(packet);
		break;
	case PacketTypes::START_GAME:
		ReceiveStartGamePacket(packet);
		break;
	case PacketTypes::END_GAME:
		ReceiveEndGamePacket(packet);
		break;
	default:
		std::cout << "No se ha identificado el tipo de paquete" << std::endl;
		break;
	}

	packet.clear();
}

void ServerPacketTypesManager::SendData(sf::TcpSocket& socket, sf::Packet& packet)
{
	if (socket.send(packet) == sf::Socket::Status::Done) {
		std::cout << "Enviando paquete..." << std::endl;
	}
	else {
		std::cerr << "Error al enviar el paquete" << std::endl;
	}
}

void ServerPacketTypesManager::ReceiveP2PTurnActionPacket(sf::Packet data)
{
	std::cout << "Recibido paquete de turno" << std::endl;

	int column, row, currentPlayer;

	data >> column >> row >> currentPlayer;

	//-----IA----
	NT->PushPendingMove(Move(row, column), currentPlayer);
	//-----------
}

void ServerPacketTypesManager::ReceiveP2PEndGamePacket(sf::Packet data)
{
	std::cout << "Recibido paquete de fin de la partida" << std::endl;
}

void ServerPacketTypesManager::SendHandshake(sf::TcpSocket& server)
{
	sf::Packet packet;
	packet << PacketTypes::HANDSHAKE << handshakeMessage;
	SendData(server, packet);
}

void ServerPacketTypesManager::SendLoginAttempt(std::string username, std::string password, sf::TcpSocket& server)
{
	if (username.empty() || password.empty()) return;

	sf::Packet packet;
	packet << PacketTypes::LOGIN;
	packet << username;
	packet << password;
	SendData(server, packet);
}

void ServerPacketTypesManager::SendRegisterAttempt(std::string username, std::string password, sf::TcpSocket& server)
{
	if (username.empty() || password.empty()) return;

	sf::Packet packet;
	packet << PacketTypes::REGISTER;
	packet << username;
	packet << password;
	SendData(server, packet);
}

void ServerPacketTypesManager::SendLobbyCreateAttempt(std::string lobbyId, sf::TcpSocket& server)
{
	if (lobbyId.empty()) return;

	sf::Packet packet;

	packet << PacketTypes::LOBBY_CREATE;
	packet << lobbyId;

	LM->SetRoomId(lobbyId);

	SendData(server, packet);
}

void ServerPacketTypesManager::SendLobbyJoinAttempt(std::string lobbyId, sf::TcpSocket& server)
{
	if (lobbyId.empty()) return;

	sf::Packet packet;

	packet << PacketTypes::LOBBY_JOIN;
	packet << lobbyId;

	LM->SetRoomId(lobbyId);

	SendData(server, packet);
}

void ServerPacketTypesManager::SendRankingPetition(int userId, sf::TcpSocket& server)
{
	sf::Packet packet;

	packet << PacketTypes::RANKING;
	packet << userId;

	SendData(server, packet);
}

void ServerPacketTypesManager::SendStartGamePetition(std::string lobbyId, sf::TcpSocket& server)
{
	sf::Packet packet;

	packet << PacketTypes::START_GAME;
	packet << lobbyId;

	SendData(server, packet);
}

void ServerPacketTypesManager::SendTurnPacket(Move move, int currentPlayer, sf::TcpSocket& server)
{
	sf::Packet packet;

	packet << P2PPacketTypes::TURN_ACTION;

	packet << move.column;
	packet << move.row;

	packet << currentPlayer;

	SendData(server, packet);
}

void ServerPacketTypesManager::ReceiveHandshakePacket(sf::Packet data)
{
	std::string receiveMesage;
	data >> receiveMesage;
	std::cout << "Mensaje enviado del servidor: " << receiveMesage << std::endl;
}

void ServerPacketTypesManager::ReceiveLoginPacket(sf::Packet data)
{
	bool success;
	std::string username;

	data >> success;
	data >> username;

	if (success) {
		std::cout << "Login correcto! Bienvenido " << username << std::endl;
		NT->SetSuccessfulLogin(true);
		NT->SendRankingPetitionServerPacket(16);
	}
	else {
		std::cout << "Login incorrecto" << std::endl;
	}
}

void ServerPacketTypesManager::ReceiveRegisterPacket(sf::Packet data)
{
	bool success;
	std::string username;

	data >> success;
	data >> username;

	if (success) {
		std::cout << "Registro correcto! Usuario " << username << " creado" << std::endl;
		NT->SetSuccessfulLogin(true);
		NT->SendRankingPetitionServerPacket(16);

	}
	else {
		std::cout << "Registro fallido " << std::endl;
	}
}

void ServerPacketTypesManager::ReceiveLobbyCreatePacket(sf::Packet data)
{
	bool success;

	data >> success;

	bool lobbyIDIsAvailable = success;

	if (lobbyIDIsAvailable) {
		std::cout << "Lobby creado exitosamente, pasando a la sala de espera" << std::endl;
		LM->JoinRoom();
	}
	else {
		std::cout << "Ese ID no esta disponible ahora mismo, prueba uno diferente" << std::endl;
	}
}

void ServerPacketTypesManager::ReceiveLobbyJoinPacket(sf::Packet data)
{
	bool success;

	data >> success;

	bool lobbyIsAvailable = success;

	if (lobbyIsAvailable) {
		std::cout << "Te has unido al lobby exitosamente" << std::endl;
		LM->JoinRoom();
	}
	else {
		std::cout << "El lobby esta lleno o no existe" << std::endl;
	}
}

void ServerPacketTypesManager::ReceivePlayerCountPacket(sf::Packet data)
{
	std::cout << "Paquete de player count recibido" << std::endl;
	int playerCount = 0;

	data >> playerCount;

	LM->UpdatePlayerCount(playerCount);
}

void ServerPacketTypesManager::ReceiveRankingPacket(sf::Packet data)
{
	int rankingSize;
	data >> rankingSize;

	for (int i = 0; i < rankingSize; i++)
	{
		User user;
		data >> user.position;
		data >> user.userIndex;
		data >> user.nickname;
		data >> user.score;

		ranking.push_back(user);
	}

	std::cout << "\n=== TOP 10 RANKINGS ===" << std::endl;
	for (const auto& user : ranking)
	{
		std::cout << user.position << ". "
			<< user.nickname << " - "
			<< user.score << " puntos" << std::endl;
	}
}

void ServerPacketTypesManager::ReceiveStartGamePacket(sf::Packet data)
{
	int playerAmount;
	data >> playerAmount;

	SharedMemory* sharedMemory = new SharedMemory();

	for(int i = 0; i < playerAmount; ++i) {
		User user;

		std::string playerIp;
		data >> playerIp;

		unsigned short remotePort;
		data >> remotePort;

		data >> user.nickname;
		data >> user.score;

		std::cout << "Ip: " << playerIp << " y Port: " << remotePort << " del usuario " << user.nickname << std::endl;

		user.userIndex = i;
		user.position = 0;

		NT->SaveClientsInfo(playerIp, remotePort, user.nickname);
		sharedMemory->saveString("userIp" + std::to_string(user.userIndex), playerIp);
		sharedMemory->saveUser("user" + std::to_string(user.userIndex), user);
	}

	LM->SaveSharedMemory(sharedMemory);
}

void ServerPacketTypesManager::ReceiveEndGamePacket(sf::Packet data)
{
}
