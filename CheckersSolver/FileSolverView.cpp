#include "FileSolverView.h"
#include "CheckersUtil.h"
#include <iostream>

using namespace std;

FileSolverView::FileSolverView(SolverContract::Presenter* presenter)
{
	this->presenter = presenter;
	setlocale(LC_ALL, "RUS");
}

void showIncorrectInput() {
	cout << "Некорректный ввод" << endl;
}

void FileSolverView::showCheckersInput()
{
	vector<CheckerInputDto> input;

	cout << "Введите координаты фигур:" << endl;

	for (int i = 0; i < 2; i++) {
		string colorString;
		int colorCount;
		cin >> colorString >> colorCount;
		bool isWhite = false;

		colorString = toLowerCase(colorString);
		
		if (colorString == "white:" || colorString == "white") {
			isWhite = true;
		}
		else if (colorString == "black:" || colorString == "black") {
			isWhite = false;
		}
		else {
			showIncorrectInput();
			return;
		}

		if (cin.fail()) {
			showIncorrectInput();
		}

		for (int j = 0; j < colorCount; j++) {
			string positionString;
			cin >> positionString;
			bool isKing = false;
			if (toLowerCase(positionString)[0] == 'm') {
				isKing = true;
				positionString.erase(0, 1);
			}

			Position position;

			try {
				position = getPositionFromString(positionString);
			}
			catch (PositionParseException e) {
				showIncorrectInput();
				return;
			}
			input.push_back(CheckerInputDto(position, isWhite, isKing));
		}
	}

	presenter->solve(input, false, false);
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
			cout << getMoveString(move) << endl;
		}
	}
	else {
		cout << "Нельзя победить в 2-3 хода";
	}
}
