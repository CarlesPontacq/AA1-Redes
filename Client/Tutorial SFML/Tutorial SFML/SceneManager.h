#pragma once
#include <unordered_map>
#include "Scene.h"
#include "GameManager.h"
#include "LoginScene.h"
#include "LobbyScene.h"
#include <string>
#include "User.h"
#include "config.h"
#include "SharedMemory.h"

class SceneManager
{
	std::unordered_map<std::string, Scene*> scenes;
	Scene* curScene;
	SharedMemory* sharedMemory;

public:
	SceneManager() {
		//TODO: Receive all external info from server
		User user = { "eauna", 69420, 0 };

		User otherUsers[PLAYER_COUNT - 1] = {
			{"blah", 0, 1},
			{"bweh", 0, 2},
			{"blip", 0, 3}
		};

		sharedMemory = new SharedMemory();
		sharedMemory->saveUser("user", user);
		for (int i = 0; i < PLAYER_COUNT; ++i) {
			if (i == user.userIndex) continue;

			for (int j = 0; j < PLAYER_COUNT - 1; ++j) 
				if (i == otherUsers[j].userIndex) 
					sharedMemory->saveUser("user" + i, otherUsers[j]);
		}

		scenes["Game"] = new GameScene();
		scenes["Login"] = new LoginScene();
		scenes["Lobby"] = new LobbyScene();
		curScene = scenes["Login"];
		curScene->enter(sharedMemory);
	}

	bool update(sf::RenderWindow& window) {
		if (curScene->nextScene != "") {
			curScene->exit();
			curScene = scenes[curScene->nextScene];
			curScene->enter(sharedMemory);
		}

		return curScene->update(window);
	}
};

