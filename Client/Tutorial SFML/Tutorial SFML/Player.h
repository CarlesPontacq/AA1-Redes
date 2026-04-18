#pragma once
#include "style.h"
#include "User.h"
#include <SFML/Graphics.hpp>

struct Player
{
	sf::RectangleShape rectangle;
	sf::Font* arial;
	sf::Text nick;

	Player() : arial(new sf::Font("arial.ttf")), nick(*arial) {}

	Player(User user) : arial(new sf::Font("arial.ttf")), nick(*arial) {
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

