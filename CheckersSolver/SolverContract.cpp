#include "SolverContract.h"

CheckerInputDto::CheckerInputDto(Position position, bool isWhite, bool isKing) {
	this->position = position;
	this->isWhite = isWhite;
	this->isKing = isKing;
}