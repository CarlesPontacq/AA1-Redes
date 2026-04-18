#pragma once
#include "User.h"
#include "Board.h"
#include "PlayerManager.h"

class GameManager
{
	sf::RenderWindow* window;

	User user;
	User otherUsers[PLAYER_COUNT - 1];
	Board board;
	PlayerManager playerManager;
	int currentPlayer;
	std::vector<bool> winners;

	bool countdownActive = false;
	sf::Clock countdownClock;

public:

	GameManager(User _user, User _otherUsers[PLAYER_COUNT - 1]) :
	user(_user), currentPlayer(0), playerManager(_user, _otherUsers)
	{
		for (int i = 0; i < PLAYER_COUNT - 1; ++i) otherUsers[i] = _otherUsers[i];

		window = new sf::RenderWindow(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), WINDOW_NAME);

		board = Board();

		for (int i = 0; i < PLAYER_COUNT; ++i)
			winners.push_back(false);
	}

	~GameManager() {
		delete window;
	}

	bool update() {

		if (!window->isOpen()) return false;

		playerTimer();

		while (const std::optional event = window->pollEvent())
			handleEvent(*event);

		render();

		return true;
	}

private:

	void handleEvent(const sf::Event& event) {
		if (event.is<sf::Event::Closed>())
			window->close();

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
	}

	void render() {
		window->clear(sf::Color(0x000000FF));

		board.render(*window);
		playerManager.render(*window);

		window->display();
	}

	void playTurn(int posX, int posY) {
		if (!board.validClickPos(posX, posY)) return;

		int row = board.screenToBoardY(posY);
		int column = board.screenToBoardX(posX);

		if(!board.setCell(row, column, currentPlayer))
			return;

		if (board.checkWin(row, column)) 
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

