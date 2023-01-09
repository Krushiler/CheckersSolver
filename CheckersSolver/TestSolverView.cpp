#include "TestSolverView.h"
#include "CheckersUtil.h"
#include <iostream>

TestSolverView::TestSolverView(SolverContract::Presenter* presenter)
{
	this->presenter = presenter;
	setlocale(LC_ALL, "RUS");
}

void TestSolverView::showCheckersInput()
{
	std::vector<CheckerInputDto> input;
	input.push_back(CheckerInputDto(std::make_pair(1, 0), false, false));
	input.push_back(CheckerInputDto(std::make_pair(0, 1), false, false));
	input.push_back(CheckerInputDto(std::make_pair(0, 3), false, false));
	input.push_back(CheckerInputDto(std::make_pair(1, 4), false, false));
	input.push_back(CheckerInputDto(std::make_pair(1, 6), false, false));
	input.push_back(CheckerInputDto(std::make_pair(0, 7), false, false));
	input.push_back(CheckerInputDto(std::make_pair(3, 6), false, false));
	input.push_back(CheckerInputDto(std::make_pair(7, 4), false, true));

	input.push_back(CheckerInputDto(std::make_pair(6, 5), true, false));
	input.push_back(CheckerInputDto(std::make_pair(5, 6), true, false));
	input.push_back(CheckerInputDto(std::make_pair(6, 7), true, false));

	presenter->solve(input, true, true);
}

void TestSolverView::showResult(Field* startField, SolverResult result)
{
	if (result.success == true) {
		std::cout << getFieldString(startField) << std::endl << "________" << std::endl << std::endl;;
		for (auto& move : result.moves) {
			startField->moveChecker(move);
			std::cout << getFieldString(startField) << std::endl << "________" << std::endl << std::endl;
		}
		for (auto& move : result.moves) {
			std::cout << getMoveString(move) << std::endl;
		}
	}
	else {
		std::cout << "Нельзя победить в 2-3 хода\n";
	}
	system("pause");
}
