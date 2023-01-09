#pragma once
#include "SolverContract.h"
#include <iostream>
#include <fstream>

class FileSolverView : public SolverContract::View
{
private:
	SolverContract::Presenter* presenter;
	std::istream& istream;
	std::ostream& ostream;

	void showIncorrectInput();
public:
	FileSolverView(SolverContract::Presenter* presenter, std::istream& istream, std::ostream& ostream);

	void showCheckersInput();
	void showResult(Field* startField, SolverResult result, int combinationsChecked);
};