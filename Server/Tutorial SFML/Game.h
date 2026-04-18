#pragma once
#include "Player.h"

class GameRoom
{
public:
	GameRoom(std::string roomId)
		: id(roomId) {};

private:
	std::string id;
	Player players[4];
	int playersAdded = 0;

public:
	std::string GetId() { return id; }
	void AddPlayer(Player player)
	{
		players[playersAdded] = player;
		playersAdded++;
	}

	bool IsFull() { return playersAdded == 4; }
};