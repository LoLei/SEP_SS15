//------------------------------------------------------------------------------
// Position.h
//
// Group: 9, study assistant: Philipp Loibl
//
// Authors: Verena Niederwanger (1430778)
//------------------------------------------------------------------------------
//
#ifndef POSITION_H
#define POSITION_H
#include <string>

class Position
{
private:
	signed int x;
	signed int y;
	std::string input;

public:
	Position();
	Position(signed int x, signed int y);
	Position(const Position &copy);
	~Position();

	signed int getX() const { return x; }
	signed int getY() const { return y; }

	bool parse(std::string input);
	std::string toString();
};

#endif

