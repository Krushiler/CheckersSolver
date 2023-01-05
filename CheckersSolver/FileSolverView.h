#pragma once
#include "SolverContract.h"

class FileSolverView : public SolverContract::View
{
private:
	SolverContract::Presenter* presenter;
public:
	FileSolverView(SolverContract::Presenter* presenter);

	void showCheckersInput();
	void showResult(Field* startField, SolverResult result);
};

