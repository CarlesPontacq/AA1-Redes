#pragma once
#include <string>
#include "SharedMemory.h"

#define LM LobbyManager::Instance()

#define MAX_PLAYERS 4

class LobbyManager
{
public:
	static LobbyManager* Instance() {
		static LobbyManager lm;

		return &lm;
	}

private:
	bool roomJoined = false;
	bool gameStarted = false;
	int playerCount = 1;
	std::string roomId = "";

	SharedMemory sharedMemory;
	bool actualizedSharedMemory = false;


public:
	void JoinRoom()
	{
		roomJoined = true;
	}

	void StartGame() 
	{ 


		gameStarted = true;
	}

	bool GetRoomJoined() { return roomJoined; }
	bool GetGameStarted() { return gameStarted; }
	bool GetActualizedSharedMemory() { return actualizedSharedMemory; }
	void UpdatePlayerCount(int newPlayerCount) { playerCount = newPlayerCount; }
	int GetUpdatedPlayerCount() { return playerCount; }
	void SetRoomId(std::string newRoomId) { roomId = newRoomId; }
	std::string GetRoomId() { return roomId; }

	void SaveSharedMemory(SharedMemory* _sharedMemory) {
		sharedMemory.CopySharedMemoryData(_sharedMemory);
		actualizedSharedMemory = true;
	}

private:
	LobbyManager() = default;
	LobbyManager(const LobbyManager& lm) = delete;
	LobbyManager& operator=(const LobbyManager& lm) = delete;
	~LobbyManager() = default;

};
