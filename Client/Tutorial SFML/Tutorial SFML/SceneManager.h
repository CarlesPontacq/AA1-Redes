#pragma once
#include <unordered_map>
#include "Scene.h"
#include "GameManager.h"
#include "LoginScene.h"
#include <string>
#include "User.h"
#include "config.h"
class SceneManager
{
	std::unordered_map<std::string, Scene*> scenes;
	Scene* curScene;

public:
	SceneManager() {
		//TODO: Receive all external info from server
		User user = { "eauna", 69420, 0 };

		User otherUsers[PLAYER_COUNT - 1] = {
			{"blah", 0, 1},
			{"bweh", 0, 2},
			{"blip", 0, 3}
		};

		scenes["Game"] = new GameScene(user, otherUsers);
		scenes["Login"] = new LoginScene();
		curScene = scenes["Login"];
		curScene->enter();
	}

	bool update(sf::RenderWindow& window) {
		if (curScene->nextScene != "") {
			curScene->exit();
			curScene = scenes[curScene->nextScene];
			curScene->enter();
		}

		return curScene->update(window);
	}
};

