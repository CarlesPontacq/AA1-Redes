#pragma once
struct Move
{
	int row;
	int column;

	Move(int _row, int _column) : row(_row), column(_column) {}
};

const Move noMove = { -1, 0 };
const Move nullMove = { -1, -1 };

