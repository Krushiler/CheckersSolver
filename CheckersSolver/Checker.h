#pragma once
#include <vector>

typedef std::pair<int, int> Position;

class Field;
class Checker;

struct CheckersMove {
	Position startPos;
	Position endPos;
	Checker* cutChecker;

	CheckersMove(Position startPos, Position endPos, Checker* cutChecker);
};

class Checker
{
public:
	Position position;
	bool isWhite;
	bool isKing;

	Field* field;

	Checker(Position position, bool isWhite, bool isKing, Field* field);

	Checker(const Checker& checker, Field* field);

	std::vector<CheckersMove> findCutMoves();
	std::vector<CheckersMove> findMoves();

	bool canBecomeKing();

	friend class Field;
};