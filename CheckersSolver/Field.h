#pragma once
#include "Checker.h"
#include <functional>

class Field
{
private:
	void findAvaliableMoves();
public:
	Checker* cells[8][8];
	bool whiteStep;

	std::vector<CheckersMove> avaliableMoves;
	
	Field();

	Field(const Field& field);

	~Field();

	Checker* const& operator[](Position position) const;

	void moveChecker(CheckersMove move);

	bool inArea(Position position);

	std::vector<Checker*> getCheckersWhere(std::function <bool (Checker*)> condition);
	std::vector<Checker*> getWhiteCheckers();
	std::vector<Checker*> getBlackCheckers();

	int getScoreDifference(bool whiteWinNeeded);

	void addChecker(Position position, bool isWhite, bool isKing);
};