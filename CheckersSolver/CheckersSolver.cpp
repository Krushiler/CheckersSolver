#include "CheckersSolver.h"

SolverResult::SolverResult() {
    success = false;
    movesCount = 0;
    moves = std::vector<CheckersMove>();
}

SolverResult::SolverResult(std::vector<CheckersMove> moves, int movesCount, bool success) {
    this->moves = moves;
    this->movesCount = movesCount;
    this->success = success;
}

SolverResult CheckersSolver::findMoves(Field* field, std::vector<CheckersMove> moves, int movesCount, bool whiteStart, bool whiteWinNeeded)
{
    bool whiteCheckersEmpty = field->getWhiteCheckers().empty();
    bool blackCheckersEmpty = field->getBlackCheckers().empty();

    if (movesCount > 3 || (whiteWinNeeded && whiteCheckersEmpty || !whiteWinNeeded && blackCheckersEmpty)) {
        delete field;
        return SolverResult(moves, movesCount, false);
    }
    if (whiteWinNeeded && blackCheckersEmpty || !whiteWinNeeded && whiteCheckersEmpty) {
        return SolverResult(moves, movesCount, true);
    }

    auto fieldMoves = field->avaliableMoves;
    for (auto& move : fieldMoves) {

        std::vector<CheckersMove> newMoves(moves);

        newMoves.push_back(move);

        Field* newField = new Field(*field);
        bool prevStep = newField->whiteStep;

        newField->moveChecker(move);

        bool newStep = newField->whiteStep;

        int newMovesCount = movesCount;

        if (prevStep != newStep && newStep == whiteStart) {
            newMovesCount++;
        }

        auto result = findMoves(newField, newMoves, newMovesCount, whiteStart, whiteWinNeeded);

        if (result.success) {
            return result;
        }
    }

    return SolverResult(moves, movesCount, false);
}

SolverResult CheckersSolver::getMinimalMovesCount(Field* field, bool whiteFirstStep, bool whiteWinNeeded)
{
    auto newField = new Field(*field);
    newField->whiteStep = whiteFirstStep;

    return findMoves(newField, std::vector<CheckersMove>(), 0, whiteFirstStep, whiteWinNeeded);
}
