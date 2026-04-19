#pragma once
struct Move
{
	int row;
	int column;

	Move(int _row, int _column) : row(_row), column(_column) {}
};

Move noMove = { -1, 0 };
Move nullMove = { -1, -1 };

