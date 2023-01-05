#pragma once
#include "SolverContract.h"

class SolverPresenter : public SolverContract::Presenter {
private:
	SolverContract::View* view;
public:
	void attachView(SolverContract::View* view);
	void solve(std::vector<CheckerInputDto> inputDtos, bool firstWhiteStep, bool whiteWinNeeded);
};
