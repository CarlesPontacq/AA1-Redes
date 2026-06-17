#pragma once
#include "User.h"
#include "Board.h"
#include "Scene.h"
#include "Object.h"
#include "CountdownTimer.h"
#include "ObjectShape.h"
#include "ObjectText.h"
#include "ObjectCircle.h"
#include "GameStyle.h"
#include <string>
#include <vector>

class GameScene : public Scene
{
	User user;
	std::vector<User> otherUsers;

	sf::Font* font = nullptr;

public:
	void enter(SharedMemory* _sharedMemory) override {
		sharedMemory = _sharedMemory;

		font = new sf::Font(FONT_PATH);

		std::vector<User> users;
		for (int i = 0; i < PLAYER_COUNT; ++i) {
			User user;
			sharedMemory->getUser("user" + std::to_string(i), user);
			users.push_back(user);
		}

		// =========================
		// BACKGROUND
		// =========================
		sf::RectangleShape background;
		background.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT });
		background.setPosition({ 0.f, 0.f });
		background.setFillColor(gameBackgroundColor);
		objects.push_back(new ObjectShape(background));

		// =========================
		// TITLE
		// =========================
		sf::Text title(*font, gameTitleText);
		title.setCharacterSize(gameTitleSize);
		title.setFillColor(gameTitleColor);
		{
			sf::FloatRect bounds = title.getLocalBounds();
			title.setPosition({
				WINDOW_WIDTH * 0.5f - bounds.size.x / 2.f - bounds.position.x,
				WINDOW_HEIGHT * 0.06f
				});
		}
		objects.push_back(new ObjectText(title));

		sf::Text subtitle(*font, gameSubtitleText);
		subtitle.setCharacterSize(gameSubtitleSize);
		subtitle.setFillColor(gameSubtitleColor);
		{
			sf::FloatRect bounds = subtitle.getLocalBounds();
			subtitle.setPosition({
				WINDOW_WIDTH * 0.5f - bounds.size.x / 2.f - bounds.position.x,
				WINDOW_HEIGHT * 0.115f
				});
		}
		objects.push_back(new ObjectText(subtitle));

		// =========================
		// BOARD PANEL
		// =========================
		sf::Vector2f boardPanelPos = {
			WINDOW_WIDTH * boardAnchorX - 20.f,
			WINDOW_HEIGHT * boardAnchorY - 20.f
		};

		sf::RectangleShape boardPanelShadow;
		boardPanelShadow.setSize(boardPanelSize);
		boardPanelShadow.setPosition({ boardPanelPos.x + 8.f, boardPanelPos.y + 10.f });
		boardPanelShadow.setFillColor(sf::Color(0, 0, 0, 100));
		objects.push_back(new ObjectShape(boardPanelShadow));

		sf::RectangleShape boardPanel;
		boardPanel.setSize(boardPanelSize);
		boardPanel.setPosition(boardPanelPos);
		boardPanel.setFillColor(gamePanelColor);
		boardPanel.setOutlineThickness(gamePanelOutlineThickness);
		boardPanel.setOutlineColor(gamePanelOutlineColor);
		objects.push_back(new ObjectShape(boardPanel));

		sf::RectangleShape boardAccent;
		boardAccent.setSize({ boardPanelSize.x, 6.f });
		boardAccent.setPosition(boardPanelPos);
		boardAccent.setFillColor(gameAccentXColor);
		objects.push_back(new ObjectShape(boardAccent));

		// =========================
		// PLAYERS PANEL
		// =========================
		sf::Vector2f playersPanelPos = {
			WINDOW_WIDTH * playersAnchorX - 20.f,
			WINDOW_HEIGHT * playersAnchorY - 60.f
		};

		sf::RectangleShape playersPanelShadow;
		playersPanelShadow.setSize(playersPanelSize);
		playersPanelShadow.setPosition({ playersPanelPos.x + 8.f, playersPanelPos.y + 10.f });
		playersPanelShadow.setFillColor(sf::Color(0, 0, 0, 100));
		objects.push_back(new ObjectShape(playersPanelShadow));

		sf::RectangleShape playersPanel;
		playersPanel.setSize(playersPanelSize);
		playersPanel.setPosition(playersPanelPos);
		playersPanel.setFillColor(gamePanelColor);
		playersPanel.setOutlineThickness(gamePanelOutlineThickness);
		playersPanel.setOutlineColor(gamePanelOutlineColor);
		objects.push_back(new ObjectShape(playersPanel));

		sf::RectangleShape playersAccent;
		playersAccent.setSize({ playersPanelSize.x, 6.f });
		playersAccent.setPosition(playersPanelPos);
		playersAccent.setFillColor(gameAccentOColor);
		objects.push_back(new ObjectShape(playersAccent));

		sf::Text playersTitle(*font, "Players");
		playersTitle.setCharacterSize(24);
		playersTitle.setFillColor(gameTitleColor);
		playersTitle.setPosition({
			playersPanelPos.x + 20.f,
			playersPanelPos.y + 16.f
			});
		objects.push_back(new ObjectText(playersTitle));

		// =========================
		// TIMER PANEL
		// =========================
		sf::Vector2f timerPanelPos = {
			WINDOW_WIDTH * timerPanelAnchorX - 20.f,
			WINDOW_HEIGHT * timerPanelAnchorY
		};

		sf::RectangleShape timerPanelShadow;
		timerPanelShadow.setSize(timerPanelSize);
		timerPanelShadow.setPosition({ timerPanelPos.x + 8.f, timerPanelPos.y + 10.f });
		timerPanelShadow.setFillColor(sf::Color(0, 0, 0, 100));
		objects.push_back(new ObjectShape(timerPanelShadow));

		sf::RectangleShape timerPanel;
		timerPanel.setSize(timerPanelSize);
		timerPanel.setPosition(timerPanelPos);
		timerPanel.setFillColor(timerPanelColor);
		timerPanel.setOutlineThickness(gamePanelOutlineThickness);
		timerPanel.setOutlineColor(timerPanelOutlineColor);
		objects.push_back(new ObjectShape(timerPanel));

		sf::RectangleShape timerAccent;
		timerAccent.setSize({ timerPanelSize.x, 6.f });
		timerAccent.setPosition(timerPanelPos);
		timerAccent.setFillColor(gameAccentXColor);
		objects.push_back(new ObjectShape(timerAccent));

		sf::Text timerTitle(*font, "Turn Timer");
		timerTitle.setCharacterSize(24);
		timerTitle.setFillColor(gameTitleColor);
		timerTitle.setPosition({
			timerPanelPos.x + 20.f,
			timerPanelPos.y + 16.f
			});
		objects.push_back(new ObjectText(timerTitle));

		// =========================
		// GAME OBJECTS
		// =========================
		PlayerManager* playerManager = new PlayerManager(users[NT->GetMainPlayerIndex()], users, *font);
		Board* board = new Board(playerManager);
		CountdownTimer* countdown = new CountdownTimer(playerManager);

		objects.push_back(static_cast<Object*>(playerManager));
		objects.push_back(static_cast<Object*>(board));
		objects.push_back(static_cast<Object*>(countdown));
	}
};