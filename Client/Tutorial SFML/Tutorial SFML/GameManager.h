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
	User otherUsers[PLAYER_COUNT - 1];

	sf::Font* arial;
	InputField* inputField;

public:

	GameScene(User _user, User _otherUsers[PLAYER_COUNT - 1]) :
		user(_user), arial(new sf::Font("arial.ttf"))
	{
		PlayerManager* playerManager = new PlayerManager(_user, _otherUsers, *arial);

		for (int i = 0; i < PLAYER_COUNT - 1; ++i) otherUsers[i] = _otherUsers[i];

		Board* board = new Board(playerManager);

		CountdownTimer* countdown = new CountdownTimer(playerManager);

		sf::RectangleShape inputRect;
		sf::Text inputText(*arial);
		inputField = new InputField(inputRect, inputText);
		inputField->isSelected = true;

		objects.push_back(static_cast<Object*>(playerManager));
		objects.push_back(static_cast<Object*>(board));
		objects.push_back(static_cast<Object*>(countdown));
		objects.push_back(static_cast<Object*>(inputField));
	}
};

