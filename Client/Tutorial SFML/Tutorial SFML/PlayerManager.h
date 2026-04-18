#pragma once
#include "Player.h"
#include "User.h"
class PlayerManager
{
	Player players[PLAYER_COUNT];

public:
	PlayerManager(User user, User otherUsers[PLAYER_COUNT - 1]) {
		for (int index = 0; index < PLAYER_COUNT; ++index)
			if (user.userIndex == index)
				players[index] = Player(user);
			else for (int othersIndex = 0; othersIndex < PLAYER_COUNT - 1; ++othersIndex) 
					if (otherUsers[othersIndex].userIndex == index) 
						players[index] = Player(otherUsers[othersIndex]);
	}

	void render(sf::RenderWindow& window) {
		for (Player player : players) {
			window.draw(player.rectangle);
			window.draw(player.nick);
		}
	}
};

