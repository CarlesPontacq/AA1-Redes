#pragma once
#include "Scene.h"
#include "GameManager.h"
#include "Button.h"

class LoginScene : public Scene
{

	sf::Font* arial;

public:
	void enter() override {
		arial = new sf::Font("arial.ttf");

		//Nickname
		sf::RectangleShape nicknameRect;
		nicknameRect.setSize({ WINDOW_WIDTH * 0.3f, WINDOW_HEIGHT * 0.15f });
		nicknameRect.setPosition({ WINDOW_WIDTH * 0.5f - nicknameRect.getSize().x / 2, WINDOW_HEIGHT * 0.1f });
		nicknameRect.setFillColor(sf::Color::Red);
		InputField* nicknameField = new InputField(nicknameRect, sf::Text(*arial), 10);

		objects.push_back(nicknameField);

		//Password
		sf::RectangleShape passwordRect;
		passwordRect.setSize({ WINDOW_WIDTH * 0.3f, WINDOW_HEIGHT * 0.15f });
		passwordRect.setPosition({ WINDOW_WIDTH * 0.5f - passwordRect.getSize().x / 2, WINDOW_HEIGHT * 0.3f });
		passwordRect.setFillColor(sf::Color::Red);
		InputField* passwordField = new InputField(passwordRect, sf::Text(*arial), 10);
		passwordField->isCensored = true;

		objects.push_back(passwordField);

		//Login
		sf::RectangleShape loginRect;
		loginRect.setSize({ WINDOW_WIDTH * 0.2f, WINDOW_HEIGHT * 0.15f });
		loginRect.setPosition({ WINDOW_WIDTH * 0.5f - loginRect.getSize().x / 2, WINDOW_HEIGHT * 0.5f });
		loginRect.setFillColor(sf::Color::Red);
		Button* loginButton = new Button(loginRect, sf::Text(*arial, "Login"), []() {std::cout << "Hi";});

		objects.push_back(loginButton);

		//Register
		sf::RectangleShape registerRect;
		registerRect.setSize({ WINDOW_WIDTH * 0.2f, WINDOW_HEIGHT * 0.15f });
		registerRect.setPosition({ WINDOW_WIDTH * 0.5f - registerRect.getSize().x / 2, WINDOW_HEIGHT * 0.7f });
		registerRect.setFillColor(sf::Color::Red);
		Button* registerButton = new Button(registerRect, sf::Text(*arial, "Register"), [&]() { this->nextScene = "Game"; });

		objects.push_back(registerButton);
	}
};

