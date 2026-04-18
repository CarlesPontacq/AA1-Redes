#pragma once
#include "style.h"
#include "User.h"
#include <SFML/Graphics.hpp>

struct Player
{
	sf::RectangleShape rectangle;
	
	sf::Text nick;

	Player() : nick(nullFont) {}

	Player(User user, sf::Font& font) : nick(font) {
		rectangle.setPosition({
			WINDOW_WIDTH * playersAnchorX,
			WINDOW_HEIGHT * playersAnchorY + user.userIndex * (playersHeight + playersSeparation)
			});
		rectangle.setFillColor(sf::Color::Cyan);
		rectangle.setSize({ playersWidth, playersHeight });

		nick.setString(user.nickname);
		nick.setPosition(rectangle.getPosition() + sf::Vector2f{rectangle.getSize().x * 0.2f, rectangle.getSize().y / 5});
		nick.setCharacterSize(40);
		nick.setStyle(sf::Text::Regular);
	}
};

