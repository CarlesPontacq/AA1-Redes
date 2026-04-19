#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "config.h"

const sf::Vector2f lobbyRectSize = { WINDOW_WIDTH * 0.3f, WINDOW_HEIGHT * 0.15f };
const float lobbyRectAnchorX = 0.5f;
const float lobbyRectAnchorY = 0.3f;
const sf::Color lobbyRectColour = sf::Color::Blue;
const int lobbyMaxChars = 10;

const sf::Vector2f createRectSize = { WINDOW_WIDTH * 0.2f, WINDOW_HEIGHT * 0.15f };
const float createRectAnchorX = 0.29f;
const float createRectAnchorY = 0.5f;
const sf::Color createRectColour = sf::Color::Red;
const std::string createButtonLabel = "Create Lobby";

const sf::Vector2f joinRectSize = { WINDOW_WIDTH * 0.2f, WINDOW_HEIGHT * 0.15f };
const float joinRectAnchorX = 0.51f;
const float joinRectAnchorY = 0.5f;
const sf::Color joinRectColour = sf::Color::Red;
const std::string joinButtonLabel = "Join Lobby";