#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"

class InputField : public Object
{
public:
	sf::RectangleShape box;
	sf::Text text;
	std::string str = "";
	int maxChars;
	bool isCensored = false;
	bool isSelected = false;

	InputField() : text(nullFont) {}

	InputField(sf::RectangleShape _rect, sf::Text _text, int _maxChars) : box(_rect), text(_text), maxChars(_maxChars) {}

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

		if (sf::Keyboard::Key::A <= key && key <= sf::Keyboard::Key::Z && str.size() < maxChars) 
			str.push_back(isCensored ? '*' : (char)key - (int)sf::Keyboard::Key::A + 'A');

		if (sf::Keyboard::Key::Num0 <= key && key <= sf::Keyboard::Key::Num9 && str.size() < maxChars)
			str.push_back(isCensored ? '*' : (char)key - (int)sf::Keyboard::Key::Num0 + '0');
	}

	void onClick(const sf::Event::MouseButtonPressed* mouse) {
		if (isSelected && !clickedInside(mouse->position.x, mouse->position.y) || 
			!isSelected && clickedInside(mouse->position.x, mouse->position.y))
			isSelected = !isSelected;
	}

	void render(sf::RenderWindow& window) override {
		text.setString(str);
		text.setPosition({ box.getPosition().x + text.getCharacterSize(), box.getPosition().y + box.getSize().y / 2.0f - text.getCharacterSize() / 2.0f});
		window.draw(box);
		window.draw(text);
	}

	void handleEvent(const sf::Event& event) override {
		if (const sf::Event::MouseButtonPressed* mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {

			switch (mousePressed->button)
			{
			case sf::Mouse::Button::Left:
				onClick(mousePressed);
				break;
			default:
				break;
			}
		}

		if (const sf::Event::KeyPressed* keyPressed = event.getIf<sf::Event::KeyPressed>())
			getChar(keyPressed->code);
	}
};

