#include "SolverPresenter.h"

void SolverPresenter::attachView(SolverContract::View* view)
{
	this->view = view;
	view->showCheckersInput();
}

void SolverPresenter::solve(std::vector<CheckerInputDto> inputDtos, bool firstWhiteStep, bool whiteWinNeeded)
{
    auto field = new Field();
	field->whiteStep = firstWhiteStep;
	
	for (auto inputDto : inputDtos) {
		field->addChecker(inputDto.position, inputDto.isWhite, inputDto.isKing);
	}

	CheckersSolver solver = CheckersSolver();
	auto result = solver.getMinimalMovesCount(new Field(*field), firstWhiteStep, whiteWinNeeded);

	this->view->showResult(new Field(*field), result);
}
