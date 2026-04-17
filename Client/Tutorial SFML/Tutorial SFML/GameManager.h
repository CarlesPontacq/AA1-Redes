#pragma once
#include "Board.h"

class GameManager
{
	Board board = Board();
	int currentPlayer = 0;
	std::vector<bool> winners;

public:

	void init() {
		board.init();

		for (int i = 0; i < PLAYER_COUNT; ++i)
			winners.push_back(false);
	}

	void update() {
		system("cls");
		board.render();
		while (!playTurn());
	}

	bool playTurn() {
		std::cout << "Enter turn: ";
		int row, column;
		std::cin >> column >> row;

		if(!board.setCell(row, column, currentPlayer))
			return false;

		if (board.checkWin(row, column)) 
			winners[currentPlayer] = true;

		do {
			currentPlayer++;
			currentPlayer %= PLAYER_COUNT;
			std::cout << currentPlayer << ' ' << winners[currentPlayer];
		} while (winners[currentPlayer]);

		return true;
	}
};

