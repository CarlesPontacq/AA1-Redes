#pragma once
#include "User.h"
#include "Board.h"
#include "PlayerManager.h"
#include "InputField.h"
#include "Scene.h"
#include "Object.h"
#include "CountdownTimer.h"

class GameScene : public Scene
{
	User user;
	std::vector<User> otherUsers;

	sf::Font* arial;

public:
	void enter(SharedMemory* _sharedMemory) override {
		sharedMemory = _sharedMemory;

		arial = new sf::Font("arial.ttf");

		User mainUser;
		sharedMemory->getUser("user", mainUser);

		std::vector<User> otherUsers;
		for (int i = 0; i < PLAYER_COUNT; ++i) {
			if (i == mainUser.userIndex) continue;

			User user;
			sharedMemory->getUser("user" + i, user);
			otherUsers.push_back(user);
		}

		PlayerManager* playerManager = new PlayerManager(mainUser, otherUsers, *arial);

		Board* board = new Board(playerManager);

		CountdownTimer* countdown = new CountdownTimer(playerManager);

		objects.push_back(static_cast<Object*>(playerManager));
		objects.push_back(static_cast<Object*>(board));
		objects.push_back(static_cast<Object*>(countdown));
	}
};

