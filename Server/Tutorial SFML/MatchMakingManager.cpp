#include "MatchMakingManager.h"

bool MatchMakingManager::IsAvailableRoomId(std::string roomId)
{
	for (int i = 0; i < waitingRooms.size(); i++)
	{
		if (roomId == waitingRooms[i].GetId())
			return false;
	}
	return true;
}

Player* MatchMakingManager::GetPlayer(sf::TcpSocket* playerClient)
{
	for (int i = 0; i < connectedPlayers.size(); i++)
	{
		if (playerClient == connectedPlayers[i].client)
			return &connectedPlayers[i];
	}

	return nullptr;
}

void MatchMakingManager::AddConnectedPlayer(sf::TcpSocket* playerClient, std::string username, int playerPoints)
{
	connectedPlayers.push_back(Player(playerClient, username, playerPoints));
}

bool MatchMakingManager::CreateWaitingRoom(std::string roomId, sf::TcpSocket* playerClient)
{		
	if (!IsAvailableRoomId(roomId))
		return false;
	
	GameRoom room(roomId);
	room.AddPlayer(*GetPlayer(playerClient));

	waitingRooms.push_back(GameRoom(roomId));

	return true;
}

bool MatchMakingManager::JoinWaitingRoom(std::string roomId, sf::TcpSocket* playerClient)
{
	for (int i = 0; i < waitingRooms.size(); i++)
	{
		if (roomId == waitingRooms[i].GetId())
		{
			waitingRooms[i].AddPlayer(*GetPlayer(playerClient));
		}
	}
	return false;
}
