#include "Field.h"

Field::Field() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cells[i][j] = NULL;
		}
	}
	whiteStep = false;
}

Field::Field(const Field& field) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (field.cells[i][j] != NULL) {
				cells[i][j] = new Checker(*field.cells[i][j], this);
			}
			else {
				cells[i][j] = NULL;
			}
		}
	}
	
	for (int i = 0; i < field.avaliableMoves.size(); i++) {
		avaliableMoves.push_back(field.avaliableMoves[i]);
	}
	
	whiteStep = field.whiteStep;
}

Field::~Field()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			delete cells[i][j];
		}
	}
	std::vector<CheckersMove>().swap(avaliableMoves);
}

Checker* const& Field::operator[](Position position) const
{
	return cells[position.first][position.second];
}

void Field::moveChecker(CheckersMove move)
{
	auto from = move.startPos;
	auto to = move.endPos;

	if ((*this)[from] != NULL) {
		auto movedChecker = cells[from.first][from.second];

		cells[from.first][from.second] = NULL;

		cells[to.first][to.second] = movedChecker;
		movedChecker->position = to;

		if (movedChecker->canBecomeKing()) {
			movedChecker->isKing = true;
		}

		auto cutChecker = move.cutChecker;

		if (cutChecker != NULL) {
			cells[cutChecker->position.first][cutChecker->position.second] = NULL;
			auto movedCheckerMoves = movedChecker->findCutMoves();
			if (!movedCheckerMoves.empty()) {
				avaliableMoves = movedCheckerMoves;
			}

			else {
				whiteStep = !whiteStep;
				avaliableMoves.clear();
			}
		}
		else {
			whiteStep = !whiteStep;
			avaliableMoves.clear();
		}
	}

	findAvaliableMoves();
}

bool Field::inArea(Position position)
{
	return position.first >= 0 && position.first < 8 && position.second >= 0 && position.second < 8;
}

void Field::findAvaliableMoves()
{
	if (!avaliableMoves.empty()) {
		return;
	}

	std::vector<CheckersMove> moves;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			auto checker = cells[i][j];
			if (checker != NULL && checker->isWhite == whiteStep) {
				auto cutMoves = checker->findCutMoves();
				moves.insert(moves.end(), cutMoves.begin(), cutMoves.end());
			}
		}
	}

	if (!moves.empty()) {
		avaliableMoves = moves;
		return;
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			auto checker = cells[i][j];
			if (checker != NULL && checker->isWhite == whiteStep) {
				auto cutMoves = checker->findMoves();
				moves.insert(moves.end(), cutMoves.begin(), cutMoves.end());
			}
		}
	}

	avaliableMoves = moves;

}

std::vector<Checker*> Field::getCheckersWhere(std::function <bool(Checker*)> condition)
{
	std::vector<Checker*> checkers;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (cells[i][j] != NULL && condition(cells[i][j])) {
				checkers.push_back(cells[i][j]);
			}
		}
	}
	return checkers;
}

std::vector<Checker*> Field::getWhiteCheckers()
{
	return getCheckersWhere([](Checker* checker) {
		return checker->isWhite;
	});
}

std::vector<Checker*> Field::getBlackCheckers()
{
	return getCheckersWhere([](Checker* checker) {
		return !checker->isWhite;
	});
}

void Field::addChecker(Position position, bool isWhite, bool isKing)
{
	cells[position.first][position.second] = new Checker(position, isWhite, isKing, this);
	avaliableMoves.clear();
	findAvaliableMoves();
}

int Field::getScoreDifference(bool whiteWinNeeded)
{
	int whiteScore = 0;
	int blackScore = 0;

	auto whiteCheckers = getWhiteCheckers();
	auto blackCheckers = getBlackCheckers();

	for (auto checker : whiteCheckers) {
		if (checker->isKing) whiteScore += 3;
		else whiteScore++;
	}

	for (auto checker : blackCheckers) {
		if (checker->isKing) blackScore += 3;
		else blackScore++;
	}

	int difference = whiteScore - blackScore;
	
	if (!whiteWinNeeded) {
		difference *= -1;
	}

	return difference;
}
