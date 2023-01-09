#include <iostream>
#include <fstream>
#include <string>
#include "SolverPresenter.h"
#include "TestSolverView.h"
#include "FileSolverView.h"
#include "CmdUtils.h"

using namespace std;

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "RUS");

    istream* inputStream = &cin;
    ostream* outputStream = &cout;

    char* inputFile = getCmdOption(argv, argv + argc, "-i");

    if (inputFile) {
        ifstream* file = new ifstream(inputFile);
        inputStream = static_cast<std::istream*>(file);
    }

    char* outputFile = getCmdOption(argv, argv + argc, "-o");

    if (outputFile) {
        ofstream* file = new ofstream(outputFile);
        outputStream = static_cast<std::ostream*>(file);
    }
    
    SolverPresenter* presenter = new SolverPresenter();
    SolverContract::View* view = new FileSolverView(presenter, *inputStream, *outputStream);

    //SolverContract::View* view = new TestSolverView(presenter);

    presenter->attachView(view);
}