#include "Checker.h"
#include "Field.h"
#include <iostream>
#include "SolverContract.h"

CheckersMove::CheckersMove(Position startPos, Position endPos, Checker* cutChecker, bool whiteMove)
{
	this->startPos = startPos;
	this->endPos = endPos;
	this->cutChecker = cutChecker;
	this->whiteMove = whiteMove;
}

Checker::Checker(Position position, bool isWhite, bool isKing, Field* field)
{
	this->position = position;
	this->isWhite = isWhite;
	this->isKing = isKing;
	this->field = field;
}

Checker::Checker(const Checker& checker, Field* field)
{
	position = std::make_pair(checker.position.first, checker.position.second);
	isWhite = checker.isWhite;
	isKing = checker.isKing;
	this->field = field;
}

std::vector<CheckersMove> Checker::findCutMoves()
{
	std::vector<CheckersMove> movesToCut;

	std::vector<std::pair<int, int>> directions;
	directions.push_back(std::make_pair(1, 1));
	directions.push_back(std::make_pair(1, -1));
	directions.push_back(std::make_pair(-1, -1));
	directions.push_back(std::make_pair(-1, 1));

	for (auto direction : directions) {
		
		Position currPos = std::make_pair(position.first, position.second);

		currPos.first += direction.first;
		currPos.second += direction.second;

		Checker* enemyCell = NULL;

		Position stepPos;

		while (field->inArea(currPos)) {
			auto cell = field->cells[currPos.first][currPos.second];

			if (enemyCell != NULL) {
				stepPos = std::make_pair(stepPos.first + direction.first, stepPos.second + direction.second);
				cell = field->cells[stepPos.first][stepPos.second];

				if (cell == NULL && field->inArea(stepPos)) {
					movesToCut.push_back(CheckersMove(position, stepPos, enemyCell, isWhite));
				}
				else {
					break;
				}
				continue;
			}

			if (cell != NULL) {
				enemyCell = cell;
				if (cell->isWhite != isWhite) {
					stepPos = std::make_pair(cell->position.first + direction.first, cell->position.second + direction.second);
					if (field->inArea(stepPos) && field->cells[stepPos.first][stepPos.second] == NULL) {
						movesToCut.push_back(CheckersMove(position, stepPos, cell, isWhite));
					}
				}
				else {
					break;
				};
			}

			if (!isKing) {
				break;
			}

			currPos.first += direction.first;
			currPos.second += direction.second;
		}
	}
	
	return movesToCut;
}

std::vector<CheckersMove> Checker::findMoves()
{
	auto cutMoves = findCutMoves();

	if (!cutMoves.empty()) {
		return cutMoves;
	}

	auto moves = std::vector<CheckersMove>();

	std::vector<std::pair<int, int>> directions;

	if (isKing) {
		directions.push_back(std::make_pair(1, 1));
		directions.push_back(std::make_pair(1, -1));
		directions.push_back(std::make_pair(-1, -1));
		directions.push_back(std::make_pair(-1, 1));
	} else if (isWhite) {
		directions.push_back(std::make_pair(-1, -1));
		directions.push_back(std::make_pair(-1, 1));
	}
	else {
		directions.push_back(std::make_pair(1, 1));
		directions.push_back(std::make_pair(1, -1));
	}

	for (auto direction : directions) {
		Position currPos = std::make_pair(position.first + direction.first, position.second + direction.second);

		while (field->inArea(currPos) && field->cells[currPos.first][currPos.second] == NULL) {
			moves.push_back(CheckersMove(position, currPos, NULL, isWhite));

			if (!isKing) {
				break;
			}

			currPos.first += direction.first;
			currPos.second += direction.second;
		}
	}

	return moves;
}

bool Checker::canBecomeKing()
{
	if (isKing) return false;
	return isWhite && position.first == 0 || !isWhite && position.first == 7;
}