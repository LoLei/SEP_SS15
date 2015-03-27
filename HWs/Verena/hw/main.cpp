//------------------------------------------------------------------------------
// main.cpp
//
// Group: 9, study assistant: Philipp Loibl
//
// Authors: Verena Niederwanger (1430778)
//------------------------------------------------------------------------------
//

#include <iostream>
#include <string>
#include <sstream>
#include "Game.h"
#include "Position.h"
#include "Color.h"
#include "Tile.h"

//------------------------------------------------------------------------------
// main function
// entry point for execution
// @param argc argument count
// @param **argv argument values
// @return return value for the OS
//
int main(int argc, char **argv)
{
	Game trax;
	std::cout << " === GAME === " << std::endl;
	std::cout << "getActivePlayer() = " << trax.getActivePlayer() << std::endl;
	trax.togglePlayer();
	std::cout << "getActivePlayer() = " << trax.getActivePlayer()
		<< " after togglePlayer" << std::endl;

	Position position(3, 4);
	std::cout << " === POSITION === " << std::endl;
	std::cout << "getX() = " << position.getX() << " getY() = " << position.getY()
		<< std::endl;
	std::cout << "toString() = " << position.toString() << std::endl;
	std::cout << "parse((2,5)) = " << position.parse("(2,5)") << std::endl;
	std::cout << "parse((14)) = " << position.parse("(14)") << std::endl;
	std::cout << "parse((1,4) = " << position.parse("(1,4") << std::endl;
	std::cout << "parse((2,-5)) = " << position.parse("(2,-5)") << std::endl;
	std::cout << "toString() = " << position.toString() << std::endl;


	Tile(Tile::TYPE_CROSS, COLOR_RED);
	std::cout << " ==== trax.run() === " << std::endl;
	trax.run();

	return 0;
}
