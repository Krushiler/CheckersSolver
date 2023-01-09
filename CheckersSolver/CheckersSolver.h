#pragma once
#include "Field.h"

struct SolverResult {
    std::vector<CheckersMove> moves;
    int movesCount;
    bool success;
    int score;

    SolverResult();

    SolverResult(std::vector<CheckersMove> moves, int movesCount, bool success, int score);
};


class CheckersSolver
{
private:
    SolverResult findMoves(Field* field, std::vector<CheckersMove> moves, int movesCount, bool whiteStart, bool whiteWinNeeded, int startScore);
public:

    int checkedCombinations;

    CheckersSolver();

    SolverResult getMinimalMovesCount(Field* field, bool whiteFirstStep, bool whiteWinNeeded);
};

