#pragma once

#define WINDOW_NAME "AA1 Nets"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define BOARD_WIDTH 6
#define BOARD_HEIGHT 6
#define PLAYER_COUNT 4

#define PLAYER_COUNTDOWN 20.0f //In seconds

const sf::Color colours[PLAYER_COUNT + 1] = {
		sf::Color::Black, //Default
		sf::Color::Red,
		sf::Color::Green,
		sf::Color::Blue,
		sf::Color::Yellow
};