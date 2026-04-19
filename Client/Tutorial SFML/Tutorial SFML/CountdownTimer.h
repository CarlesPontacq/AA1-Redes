#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "PlayerManager.h"
#include "Move.h"

class CountdownTimer : public Object
{
private:
	PlayerManager* playerManager;
	bool countdownActive = false;
	sf::Clock countdownClock;

public:

	CountdownTimer(PlayerManager* _playerManager) : playerManager(_playerManager) {}

	void update() override {
		if (playerManager->currentPlayer != playerManager->user.userIndex) return;

		if (!countdownActive) {
			countdownActive = true;
			countdownClock.restart();
		}

		if (countdownClock.getElapsedTime().asSeconds() < PLAYER_COUNTDOWN) return;

		playerManager->nextPlayer(noMove);
		countdownActive = false;
	}
};

