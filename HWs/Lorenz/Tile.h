// TODO: Add private copy constructor

#ifndef TILE_H
#define TILE_H
#include "Color.h"

class Tile
{
public:
  enum Type
  {
    TYPE_CROSS = 1,
    TYPE_CURVE_1 = 2,
    TYPE_CURVE_2 = 3
  };
private:
  Color top_color_;
  Type side_;
public:
  Tile() : side_(TYPE_CROSS), top_color_(COLOR_RED) {}; // Default constructor inline
  Tile(Type side, Color orientation); // Constructor
  ~Tile();
};

#endif