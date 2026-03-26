#pragma once

#define PTM PacketTypesManager::Instance

enum class PacketTypes
{
	HANDSHAKE, LOGIN, REGISTER, LOOBY_CREATE, LOBBY_JOIN, RANKING, START_GAME, END_GAME
};

class PacketTypesManager
{
public:
	static PacketTypesManager* Instance() {
		static PacketTypesManager ptm;

		return &ptm;
	}

private:

public:

private:
	PacketTypesManager() = default;
	PacketTypesManager(const PacketTypesManager& ptm) = delete;
	PacketTypesManager& operator=(const PacketTypesManager& ptm) = delete;
	~PacketTypesManager() = default;
};

