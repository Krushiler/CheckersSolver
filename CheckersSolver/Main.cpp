#include <iostream>
#include <string>
#include "SolverPresenter.h"
#include "TestSolverView.h"
#include "FileSolverView.h"

using namespace std;

int main()
{
    SolverPresenter* presenter = new SolverPresenter();
    FileSolverView* view = new FileSolverView(presenter);
    presenter->attachView(view);
}