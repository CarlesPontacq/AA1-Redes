#pragma once
#include "Scene.h"
#include "config.h"
#include "InputField.h"
#include "Button.h"
#include "ServerPacketTypesManager.h"
#include "NetworkManager.h"
#include "LobbyManager.h"
#include <iostream>

class LobbyScene : public Scene
{
	sf::Font* arial;

public:
	void enter(SharedMemory* _sharedMemory) override {
		arial = new sf::Font("arial.ttf");

		//Room id input
		sf::RectangleShape lobbyRect;
		lobbyRect.setSize({ WINDOW_WIDTH * 0.3f, WINDOW_HEIGHT * 0.15f });
		lobbyRect.setPosition({ WINDOW_WIDTH * 0.5f - lobbyRect.getSize().x / 2, WINDOW_HEIGHT * 0.3f});
		lobbyRect.setFillColor(sf::Color::Blue);
		InputField* lobbyField = new InputField(lobbyRect, sf::Text(*arial), 10);

		objects.push_back(lobbyField);

		//Create
		sf::RectangleShape createRect;
		createRect.setSize({ WINDOW_WIDTH * 0.2f, WINDOW_HEIGHT * 0.15f });
		createRect.setPosition({ WINDOW_WIDTH * 0.29f, WINDOW_HEIGHT * 0.5f });
		createRect.setFillColor(sf::Color::Red);
		Button* createButton = new Button(createRect, sf::Text(*arial, "Create lobby"), [lobbyField]() {
			NT->SendLobbyCreateAttemptPacket(lobbyField->realStr);
			});

		objects.push_back(createButton);

		//Join
		sf::RectangleShape joinRect;
		joinRect.setSize({ WINDOW_WIDTH * 0.2f, WINDOW_HEIGHT * 0.15f });
		joinRect.setPosition({ WINDOW_WIDTH * 0.51f, WINDOW_HEIGHT * 0.5f });
		joinRect.setFillColor(sf::Color::Red);
		Button* joinButton = new Button(joinRect, sf::Text(*arial, "Join lobby"), [lobbyField]() {
			NT->SendLobbyJoinAttemptPacket(lobbyField->realStr);
			});

		objects.push_back(joinButton);
	}

	bool update(sf::RenderWindow& window) override
	{
		if (LM->GetRoomJoined())
			nextScene = "Game";

		return Scene::update(window);
	}
};

