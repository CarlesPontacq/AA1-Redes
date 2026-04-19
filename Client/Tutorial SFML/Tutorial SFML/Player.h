#pragma once
#include "GameStyle.h"
#include "User.h"
#include <SFML/Graphics.hpp>

struct Player
{
	sf::RectangleShape rectangle;
	sf::Text nick;
	bool isCurrent = false;

	Player() : nick(nullFont) {}

	Player(User user, sf::Font& font) : nick(font) {
		rectangle.setPosition({
			WINDOW_WIDTH * playersAnchorX,
			WINDOW_HEIGHT * playersAnchorY + user.userIndex * (playersHeight + playersSeparation)
			});
		rectangle.setFillColor(playersBackground);
		rectangle.setSize({ playersWidth, playersHeight });

		nick.setString(user.nickname);

		//Center text
		nick.setPosition({
			rectangle.getPosition().x + rectangle.getSize().x / 2.0f - nick.getCharacterSize() / 2.0f * nick.getString().getSize() / 2.0f,
			rectangle.getPosition().y + rectangle.getSize().y / 2.0f - nick.getCharacterSize() / 2.0f
			});

		nick.setCharacterSize(playersCharacterSize);
		nick.setStyle(playersTextStyle);
	}

	void render(sf::RenderWindow& window) {
		rectangle.setFillColor(isCurrent ? activePlayersBackground : playersBackground);
		window.draw(rectangle);
		window.draw(nick);
	}
};

