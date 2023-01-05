#pragma once
#include "Field.h"
#include "CheckersSolver.h"

struct CheckerInputDto {
	Position position;
	bool isWhite;
	bool isKing;

	CheckerInputDto(Position position, bool isWhite, bool isKing);
};

namespace SolverContract {
	class View {
	public:
		virtual void showCheckersInput() = 0;
		virtual void showResult(Field* startField, SolverResult result) = 0;
	};

	class Presenter {
	public:
		virtual void solve(std::vector<CheckerInputDto> inputDtos, bool firstWhiteStep, bool whiteWinNeeded) = 0;
	};
}