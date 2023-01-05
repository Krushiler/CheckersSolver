#pragma once
#include "SolverContract.h"

class TestSolverView: public SolverContract::View
{
private:
	SolverContract::Presenter* presenter;
public:
	TestSolverView(SolverContract::Presenter* presenter);

	void showCheckersInput();
	void showResult(Field* startField, SolverResult result);
};

