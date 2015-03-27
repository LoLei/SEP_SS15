//------------------------------------------------------------------------------
// Tile.h
//
// Group: 9, study assistant: Philipp Loibl
//
// Authors: Verena Niederwanger (1430778)
//------------------------------------------------------------------------------
//
#ifndef TILE_H
#define TILE_H
#include "Color.h"

class Tile
{
private:
	Tile(const Tile &copy);
public:
	enum Type
	{
		TYPE_CROSS = 1,
		TYPE_CURVE_1 = 2,
		TYPE_CURVE_2 = 3
	};
	Type side;
	Color topcolor;
	Tile();
	Tile(Type side, Color topcolor );
	
	~Tile();

	
};

#endif


