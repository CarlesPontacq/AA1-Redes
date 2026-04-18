#pragma once
#include "User.h"
#include "Board.h"
#include "PlayerManager.h"
#include "InputField.h"
#include "Scene.h"
#include "Object.h"

class GameScene : public Scene
{
	User user;
	User otherUsers[PLAYER_COUNT - 1];
	Board* board;
	PlayerManager* playerManager;
	int currentPlayer;
	std::vector<bool> winners;

	bool countdownActive = false;
	sf::Clock countdownClock;

	sf::Font* arial;
	InputField* inputField;

public:

	GameScene(User _user, User _otherUsers[PLAYER_COUNT - 1]) :
		user(_user), currentPlayer(0), arial(new sf::Font("arial.ttf"))
	{
		playerManager = new PlayerManager(_user, _otherUsers, *arial);

		for (int i = 0; i < PLAYER_COUNT - 1; ++i) otherUsers[i] = _otherUsers[i];

		board = new Board();

		for (int i = 0; i < PLAYER_COUNT; ++i)
			winners.push_back(false);

		sf::RectangleShape inputRect;
		sf::Text inputText(*arial);
		inputField = new InputField(inputRect, inputText);
		inputField->isSelected = true;

		objects.push_back(static_cast<Object*>(playerManager));
		objects.push_back(static_cast<Object*>(board));
		objects.push_back(static_cast<Object*>(inputField));
	}

protected:

	void handleEvent(const sf::Event& event, sf::RenderWindow& window) override {
		if (event.is<sf::Event::Closed>())
			window.close();

		if (const sf::Event::MouseButtonPressed* mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {

			switch (mousePressed->button)
			{
			case sf::Mouse::Button::Left:
				playTurn(mousePressed->position.x, mousePressed->position.y);
				break;
			default:
				break;
			}
		}

		if (const sf::Event::KeyPressed* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
			inputField->getChar(keyPressed->code);
		}
	}

	void playTurn(int posX, int posY) {
		if (!board->validClickPos(posX, posY)) return;

		int row = board->screenToBoardY(posY);
		int column = board->screenToBoardX(posX);

		if(!board->setCell(row, column, currentPlayer))
			return;

		if (board->checkWin(row, column)) 
			winners[currentPlayer] = true;

		nextPlayer();
	}

	void nextPlayer() {
		do {
			currentPlayer++;
			currentPlayer %= PLAYER_COUNT;
		} while (winners[currentPlayer]);

		//TODO: Notify others of move and player change
	}

	void playerTimer() {
		if (currentPlayer != user.userIndex) return;

		if (!countdownActive) {
			countdownActive = true;
			countdownClock.restart();
		}

		if (countdownClock.getElapsedTime().asSeconds() < PLAYER_COUNTDOWN) return;

		nextPlayer();
		countdownActive = false;
	}
};

