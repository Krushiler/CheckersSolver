#include "FileSolverView.h"
#include "CheckersUtil.h"

using namespace std;

FileSolverView::FileSolverView(
	SolverContract::Presenter* presenter, 
	std::istream& istream, 
	std::ostream& ostream) : istream(istream), ostream(ostream), presenter(presenter) 
{}

void FileSolverView::showIncorrectInput() {
	ostream << "������������ ����" << endl;
}

void FileSolverView::showCheckersInput()
{
	vector<CheckerInputDto> input;

	std::cout << "���� ��������� �����" << '\n';
	
	try {
		input = readCheckers(istream);
	}
	catch (PositionParseException e) {
		showIncorrectInput();
		return;
	}

	std::cout << "����� �������..." << '\n';

	presenter->solve(input, true, true);
}

void FileSolverView::showResult(Field* startField, SolverResult result)
{
	if (result.success == true) {
		cout << endl;
		for (auto& move : result.moves) {
			startField->moveChecker(move);
			cout << getFieldString(startField) << endl << "________" << endl << endl;
		}
		for (auto& move : result.moves) {
			ostream << getMoveString(move) << endl;
		}
	}
	else {
		ostream << "������ �������� � 2-3 ����";
	}
}
