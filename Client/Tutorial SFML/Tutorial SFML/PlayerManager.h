#pragma once
#include "Player.h"
#include "User.h"
#include "Object.h"
class PlayerManager : public Object
{
public:
	int currentPlayer;
	Player players[PLAYER_COUNT];
	User user;
	std::vector<bool> winners;

public:
	void nextPlayer() {
		do {
			currentPlayer++;
			currentPlayer %= PLAYER_COUNT;
		} while (winners[currentPlayer]);

		//TODO: Notify others of move and player change
	}

public:
	PlayerManager() {}

	PlayerManager(User _user, std::vector<User> _otherUsers, sf::Font& font) : user(_user) {

		for (int i = 0; i < PLAYER_COUNT; ++i)
			winners.push_back(false);

		for (int index = 0; index < PLAYER_COUNT; ++index)
			if (_user.userIndex == index)
				players[index] = Player(_user, font);
			else for (int othersIndex = 0; othersIndex < PLAYER_COUNT - 1; ++othersIndex) 
					if (_otherUsers[othersIndex].userIndex == index) 
						players[index] = Player(_otherUsers[othersIndex], font);
	}

	void render(sf::RenderWindow& window) override {
		for (Player player : players) {
			window.draw(player.rectangle);
			window.draw(player.nick);
		}
	}
};

