#pragma once
#include "Scene.h"
#include "config.h"
#include "InputField.h"
#include "Button.h"
#include "ServerPacketTypesManager.h"
#include "NetworkManager.h"
#include <iostream>
#include "LobbyStyle.h"

class LobbyScene : public Scene
{
	sf::Font* font;

public:
	void enter(SharedMemory* _sharedMemory) override {
		font = new sf::Font(FONT_PATH);

		//Room id input
		sf::RectangleShape lobbyRect;
		lobbyRect.setSize(lobbyRectSize);
		lobbyRect.setPosition({ WINDOW_WIDTH * lobbyRectAnchorX - lobbyRect.getSize().x / 2.0f, WINDOW_HEIGHT * lobbyRectAnchorY});
		lobbyRect.setFillColor(lobbyRectColour);
		InputField* lobbyField = new InputField(lobbyRect, sf::Text(*font), lobbyMaxChars);

		objects.push_back(lobbyField);

		//Create
		sf::RectangleShape createRect;
		createRect.setSize(createRectSize);
		createRect.setPosition({ WINDOW_WIDTH * createRectAnchorX, WINDOW_HEIGHT * createRectAnchorY });
		createRect.setFillColor(createRectColour);
		Button* createButton = new Button(createRect, sf::Text(*font, createButtonLabel), [lobbyField]() {
			SPTM->SendLobbyCreateAttempt(lobbyField->realStr, *NT->GetServerSocket());
			std::cout << "Lobby creada con id: " << lobbyField->realStr;
			});

		objects.push_back(createButton);

		//Join
		sf::RectangleShape joinRect;
		joinRect.setSize(joinRectSize);
		joinRect.setPosition({ WINDOW_WIDTH * joinRectAnchorX, WINDOW_HEIGHT * joinRectAnchorY });
		joinRect.setFillColor(joinRectColour);
		Button* joinButton = new Button(joinRect, sf::Text(*font, joinButtonLabel), [&]() { this->nextScene = SceneOption::GAME; });

		objects.push_back(joinButton);
	}
};

