#pragma once
#include <vector>
#include <iostream>
#include "Cell.h"
#include "config.h"
class Board
{
	int width = BOARD_WIDTH;
	int height = BOARD_HEIGHT;
	std::vector<std::vector<Cell>> cells;

public:
	void init() {
		cells = std::vector<std::vector<Cell>>();
		for (int i = 0; i < height; ++i) {
			cells.push_back(std::vector<Cell>());
			for (int j = 0; j < width; ++j) cells.back().push_back(Cell());
		}
	}

	void render() {
		//TODO: Render with visuals
		for (int row = 0; row < height; ++row) {
			for (int column = 0; column < width; ++column) {
				std::cout << cells[row][column].playerIndex << ' ';
			}
			std::cout << std::endl;
		}
	}

	bool setCell(int row, int column, int player) {
		if (row < 0 || row >= width ||
			column < 0 || column >= height ||
			cells[row][column].playerIndex >= 0)
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
		return row >= 0 && row < height && column >= 0 && column < width;
	}
};

