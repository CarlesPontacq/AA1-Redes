#pragma once
#include "style.h"

struct Player
{
	sf::RectangleShape rectangle;
	//sf::Text nick;

	Player() {}

	Player(int index) {
		rectangle.setPosition({
			WINDOW_WIDTH * playersAnchorX,
			WINDOW_HEIGHT * playersAnchorY + index * (playersHeight + playersSeparation)
			});
		rectangle.setFillColor(sf::Color::Cyan);
		rectangle.setSize({ playersWidth, playersHeight });

		//nick = sf::Text(sf::Font::)
	}
};

