#include "CheckersSolver.h"

SolverResult::SolverResult() {
    success = false;
    movesCount = 0;
    moves = std::vector<CheckersMove>();
    score = 0;
}

SolverResult::SolverResult(std::vector<CheckersMove> moves, int movesCount, bool success, int score) {
    this->moves = moves;
    this->movesCount = movesCount;
    this->success = success;
    this->score = score;
}

SolverResult CheckersSolver::findMoves(Field* field, std::vector<CheckersMove> moves, int movesCount, bool whiteStart, bool whiteWinNeeded, int startScore)
{
    bool whiteCheckersEmpty = field->getWhiteCheckers().empty();
    bool blackCheckersEmpty = field->getBlackCheckers().empty();

    if (movesCount > 3 || (whiteWinNeeded && whiteCheckersEmpty || !whiteWinNeeded && blackCheckersEmpty)) {
        delete field;
        return SolverResult(moves, movesCount, false, startScore);
    }

    auto fieldMoves = field->avaliableMoves;

    std::vector<SolverResult> results;
    
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

        results.push_back(findMoves(newField, newMoves, newMovesCount, whiteStart, whiteWinNeeded, startScore));
    }

    int currentScore = field->getScoreDifference(whiteWinNeeded);

    SolverResult bestResult = SolverResult(moves, movesCount, true, currentScore);

    
    for (auto& result : results) {
        if (result.success && result.score > bestResult.score) {
            bestResult = result;
        }
    }

    return bestResult;
}

SolverResult CheckersSolver::getMinimalMovesCount(Field* field, bool whiteFirstStep, bool whiteWinNeeded)
{
    auto newField = new Field(*field);
    newField->whiteStep = whiteFirstStep;

    int scoreDifference = newField->getScoreDifference(whiteWinNeeded);
    
    return findMoves(newField, std::vector<CheckersMove>(), 0, whiteFirstStep, whiteWinNeeded, scoreDifference);
}
