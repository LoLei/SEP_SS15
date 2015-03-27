#include "Tile.h"

// Default constructor
//Tile::Tile() : side_(TYPE_CROSS), top_color_(COLOR_RED)
//{
//
//}

// Constructor
Tile::Tile(Type side, Color orientation)
{
  side_ = side;
  top_color_ = orientation;
}

// Destructor
Tile::~Tile()
{

}