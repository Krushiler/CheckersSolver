#pragma once
#include <string>
#include <iostream>
#include "Field.h"
#include "SolverContract.h"

class PositionParseException : public std::exception {};

std::string toLowerCase(std::string string);

std::string getPositionString(Position position);

std::string getMoveString(CheckersMove move);

std::string getFieldString(Field* field);

Position getPositionFromString(std::string positionString);

std::vector<CheckerInputDto> readCheckers(std::istream& cin);