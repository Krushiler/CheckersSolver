#pragma once
#include "Field.h"

struct SolverResult {
    std::vector<CheckersMove> moves;
    int movesCount;
    bool success;

    SolverResult();

    SolverResult(std::vector<CheckersMove> moves, int movesCount, bool success);
};


class CheckersSolver
{
private:
    SolverResult findMoves(Field* field, std::vector<CheckersMove> moves, int movesCount, bool whiteStart, bool whiteWinNeeded);
public:
    SolverResult getMinimalMovesCount(Field* field, bool whiteFirstStep, bool whiteWinNeeded);
};

