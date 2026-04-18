#pragma once
#include "Scene.h"
#include "config.h"
#include "InputField.h"
#include "Button.h"
#include <iostream>

class LobbyScene : public Scene
{
	sf::Font* arial;

public:
	void enter() override {
		arial = new sf::Font("arial.ttf");

		//Lobby
		sf::RectangleShape lobbyRect;
		lobbyRect.setSize({ WINDOW_WIDTH * 0.3f, WINDOW_HEIGHT * 0.15f });
		lobbyRect.setPosition({ WINDOW_WIDTH * 0.5f - lobbyRect.getSize().x / 2, WINDOW_HEIGHT * 0.1f });
		lobbyRect.setFillColor(sf::Color::Red);
		InputField* lobbyField = new InputField(lobbyRect, sf::Text(*arial), 10);

		objects.push_back(lobbyField);

		//Join
		sf::RectangleShape joinRect;
		joinRect.setSize({ WINDOW_WIDTH * 0.2f, WINDOW_HEIGHT * 0.15f });
		joinRect.setPosition({ WINDOW_WIDTH * 0.5f - joinRect.getSize().x / 2, WINDOW_HEIGHT * 0.3f });
		joinRect.setFillColor(sf::Color::Red);
		Button* joinButton = new Button(joinRect, sf::Text(*arial, "Join lobby"), []() {std::cout << "Hi";});

		objects.push_back(joinButton);

		//Lobby 2
		sf::RectangleShape lobby2Rect;
		lobby2Rect.setSize({ WINDOW_WIDTH * 0.3f, WINDOW_HEIGHT * 0.15f });
		lobby2Rect.setPosition({ WINDOW_WIDTH * 0.5f - lobby2Rect.getSize().x / 2, WINDOW_HEIGHT * 0.5f });
		lobby2Rect.setFillColor(sf::Color::Red);
		InputField* lobby2Field = new InputField(lobby2Rect, sf::Text(*arial), 10);

		objects.push_back(lobby2Field);

		//Register
		sf::RectangleShape createRect;
		createRect.setSize({ WINDOW_WIDTH * 0.2f, WINDOW_HEIGHT * 0.15f });
		createRect.setPosition({ WINDOW_WIDTH * 0.5f - createRect.getSize().x / 2, WINDOW_HEIGHT * 0.7f });
		createRect.setFillColor(sf::Color::Red);
		Button* createButton = new Button(createRect, sf::Text(*arial, "Create lobby"), [&]() { this->nextScene = "Game"; });

		objects.push_back(createButton);
	}
};

