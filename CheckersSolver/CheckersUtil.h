#pragma once
#include <string>
#include "Field.h"

class PositionParseException : public std::exception {};

std::string toLowerCase(std::string string);

std::string getPositionString(Position position);

std::string getMoveString(CheckersMove move);

std::string getFieldString(Field* field);

Position getPositionFromString(std::string positionString);

