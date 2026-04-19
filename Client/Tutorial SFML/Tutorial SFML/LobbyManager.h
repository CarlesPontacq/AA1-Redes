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

public:
	void JoinRoom()
	{
		roomJoined = true;
	}

	bool GetRoomJoined() { return roomJoined; }

private:
	LobbyManager() = default;
	LobbyManager(const LobbyManager& lm) = delete;
	LobbyManager& operator=(const LobbyManager& lm) = delete;
	~LobbyManager() = default;

};
