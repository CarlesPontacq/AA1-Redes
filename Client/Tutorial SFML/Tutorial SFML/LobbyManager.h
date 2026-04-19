#pragma once

#define LM LobbyManager::Instance()

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
	void UpdatePlayerCount(int newPlayerCount) { playerCount = newPlayerCount; }
	int GetUpdatedPlayerCount() { return playerCount; }
	void SetRoomId(std::string newRoomId) { roomId = newRoomId; }
	std::string GetRoomId() { return roomId; }


private:
	LobbyManager() = default;
	LobbyManager(const LobbyManager& lm) = delete;
	LobbyManager& operator=(const LobbyManager& lm) = delete;
	~LobbyManager() = default;

};
