#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "config.h"
#include "GameStyle.h"
#include "Object.h"
#include "PlayerManager.h"

class Board : public Object
{		
	PlayerManager* playerManager;
	std::vector<std::vector<Cell>> cells;

public:

	Board(PlayerManager* _playerManager) : playerManager(_playerManager) {
		cells = std::vector<std::vector<Cell>>();
		for (int i = 0; i < BOARD_HEIGHT; ++i) {
			cells.push_back(std::vector<Cell>());
			for (int j = 0; j < BOARD_WIDTH; ++j) cells.back().push_back(Cell());
		}
	}

	void update() override {
		//TODO: Receive info from other users
		//Pseudocode:
		/*
		* Move move = NT->tryGetMove();
		* 
		* if(move == nullMove) return;
		* 
		* if(move == noMove) {
		*	playerManager->nextPlayer(move);
		* }
		* 
		* setCell(move.row, move.column, playerManager->currentPlayer);
		* 
		* if (checkWin(row, column))
		* 	playerManager->winners[playerManager->currentPlayer] = true;
		* 
		* playerManager->nextPlayer(move);
		* 
		* 
		*/
	}

	void render(sf::RenderWindow& window) override {
		sf::RectangleShape square;
		square.setSize({ boardSideLength, boardSideLength });
		square.setFillColor(sf::Color::Magenta);
		square.setPosition({ WINDOW_WIDTH * boardAnchorX, WINDOW_HEIGHT * boardAnchorY });

		window.draw(square);

		for (int row = 0; row < BOARD_HEIGHT; ++row) {
			for (int column = 0; column < BOARD_WIDTH; ++column) {
				sf::RectangleShape cell;
				cell.setSize({ 
					boardSideLength / BOARD_WIDTH * (1 - cellPadding), 
					boardSideLength / BOARD_HEIGHT * (1 - cellPadding)
					});
				cell.setFillColor(colours[cells[row][column].playerIndex + 1]);
				cell.setPosition({ 
					WINDOW_WIDTH* boardAnchorX + boardSideLength * (((float)column + cellPadding / 2) / (float)BOARD_WIDTH),
					WINDOW_HEIGHT* boardAnchorY + boardSideLength * (((float)row + cellPadding / 2) / (float)BOARD_HEIGHT) }
					);
				window.draw(cell);
			}
		}
	}

	void handleEvent(const sf::Event& event) override {
		if (const sf::Event::MouseButtonPressed* mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {

			switch (mousePressed->button)
			{
			case sf::Mouse::Button::Left:
				playTurn(mousePressed->position.x, mousePressed->position.y);
				break;
			default:
				break;
			}
		}
	}

private:
	inline bool validClickPos(int posX, int posY) {
		return
			WINDOW_WIDTH * boardAnchorX <= posX &&
			WINDOW_WIDTH * boardAnchorX + boardSideLength >= posX &&
			WINDOW_HEIGHT * boardAnchorY <= posY &&
			WINDOW_HEIGHT * boardAnchorY + boardSideLength >= posY;
	}

	inline int screenToBoardX(int x) {
		return (int)(((float)x - WINDOW_WIDTH * boardAnchorX) / boardSideLength * BOARD_WIDTH);
	}

	inline int screenToBoardY(int y) {
		return (int)(((float)y - WINDOW_HEIGHT * boardAnchorY) / boardSideLength * BOARD_HEIGHT);
	}

	bool setCell(int row, int column, int player) {
		if (cells[row][column].playerIndex >= 0)
			return false;

		cells[row][column].playerIndex = player;
		return true;
	}

	bool checkWin(int row, int column) {
		
		for (int i = -2; i <= 0; ++i)
			if (
				checkLine(row + i, column, row + i + 1, column, row + i + 2, column) ||						//Vertical
				checkLine(row, column + i, row, column + i + 1, row, column + i + 2) ||						//Horizontal
				checkLine(row + i, column + i, row + i + 1, column + i + 1, row + i + 2, column + i + 2) ||	//Major diagonal
				checkLine(row - i, column + i, row - i - 1, column + i + 1, row - i - 2, column + i + 2)	//Minor diagonal
				)
				return true;

		return false;
	}

	inline bool checkLine(int row1, int column1, int row2, int column2, int row3, int column3) {
		if (!validCell(row1, column1) || !validCell(row2, column2) || !validCell(row3, column3))
			return false;

		return cells[row1][column1].playerIndex >= 0 &&
			cells[row1][column1].playerIndex == cells[row2][column2].playerIndex &&
			cells[row2][column2].playerIndex == cells[row3][column3].playerIndex;
	}

	inline bool validCell(int row, int column) {
		return row >= 0 && row < BOARD_HEIGHT && column >= 0 && column < BOARD_WIDTH;
	}

	void playTurn(int posX, int posY) {
		if (!validClickPos(posX, posY) || playerManager->currentPlayer != playerManager->user.userIndex) return;

		int row = screenToBoardY(posY);
		int column = screenToBoardX(posX);

		if (!setCell(row, column, playerManager->currentPlayer))
			return;

		if (checkWin(row, column))
			playerManager->winners[playerManager->currentPlayer] = true;

		playerManager->nextPlayer(Move(row, column));
	}
};

