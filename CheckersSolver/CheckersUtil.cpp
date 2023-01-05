#include "CheckersUtil.h"

std::string toLowerCase(std::string string)
{
    std::string result = string;
    for (int i = 0; i < string.size(); i++) {
        if (result[i] <= 'Z' && result[i] >= 'A') {
            result[i] -= ('Z' - 'z');
        }
    }
    return result;
}

std::string getPositionString(Position position) {
	int charCode = position.second + 'A';
	return char(charCode) + std::to_string(8 - position.first);
}

std::string getMoveString(CheckersMove move) {
	return getPositionString(move.startPos) + "->" + getPositionString(move.endPos);
}

std::string getFieldString(Field* field) {
    std::string result = "";

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            auto cell = field->cells[i][j];
            if (cell != NULL) {
                if (cell->isWhite) {
                    if (cell->isKing) result += 'W';
                    else result += 'w';
                }
                else {
                    if (cell->isKing) result += 'B';
                    else result += 'b';
                }
            }
            else {
                result += '.';
            }
        }
        result += '\n';
    }

    return result;
}

Position getPositionFromString(std::string positionString)
{
    positionString = toLowerCase(positionString);
    if (positionString.size() != 2) {
        throw PositionParseException();
    }
    if (positionString[0] < 'a' || positionString[0] > 'h') {
        throw PositionParseException();
    }
    if (positionString[1] < '1' || positionString[1] > '8') {
        throw PositionParseException();
    }

    int yPos = '8' - positionString[1];
    int xPos = positionString[0] - 'a';
    return std::make_pair(yPos, xPos);
}