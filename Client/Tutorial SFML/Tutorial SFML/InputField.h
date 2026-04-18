#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"

class InputField : public Object
{
public:
	sf::RectangleShape box;
	sf::Text text;
	std::string str = "";
	bool isCensored = false;
	bool isSelected = false;

	InputField() : text(nullFont) {}

	InputField(sf::RectangleShape _rect, sf::Text _text) : box(_rect), text(_text) {}

	bool clickedInside(int posX, int posY) {
		sf::Vector2f boxPosition = box.getPosition();
		sf::Vector2f boxSize = box.getSize();
		return 
			boxPosition.x <= posX && posX <= boxPosition.x + boxSize.x &&
			boxPosition.y <= posY && posY <= boxPosition.y + boxSize.y;
	}

	void getChar(sf::Keyboard::Key key) {
		if (!isSelected) return;

		if (key == sf::Keyboard::Key::Backspace && str.size() > 0) 
			str.pop_back();

		if (sf::Keyboard::Key::A <= key && key <= sf::Keyboard::Key::Z) 
			str.push_back('A' + (char)key);
	}

	void render(sf::RenderWindow& window) override {
		text.setString(str);
		window.draw(box);
		window.draw(text);
	}

	void handleEvent(const sf::Event& event) override {
		if (const sf::Event::KeyPressed* keyPressed = event.getIf<sf::Event::KeyPressed>())
			getChar(keyPressed->code);
	}
};

