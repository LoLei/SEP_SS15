//------------------------------------------------------------------------------
// Tile.cpp
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors: Markus Pichler 1331070
// 
//------------------------------------------------------------------------------
//

#include <iostream>
#include "Tile.h"

//------------------------------------------------------------------------------
Tile::Tile(Type side, Color topcolor)
{
  side_ = side;
  topcolor_ = topcolor;
}

Tile::Tile()
{
  side_ = TYPE_CROSS;
  topcolor_ = COLOR_WHITE;
}

Tile::Tile(const Tile & src)
{
  side_ = src.side_;
  topcolor_ = src.topcolor_;
}

void Tile::setColor(Color topcolor)
{
  topcolor_ = topcolor;
}

Color Tile::getColor()
{
  return topcolor_;
}

Tile::Type Tile::getType()
{
  return side_;
}

void Tile::setType(char c)
{
  switch (c)
  {
    case '/':
      side_ = TYPE_CURVE_1;
      break;
    case '+':
      side_ = TYPE_CROSS;
      break;
    case '\\':
      side_ = TYPE_CURVE_2;
      break;
  }
}

std::string Tile::getColorOut()
{
  switch (topcolor_)
  {
    case COLOR_WHITE:
      return "White";
      break;
    case COLOR_RED:
      return "red";
      break;
  }
  return "fail";
}

std::string Tile::getTypeOut()
{
  switch (side_)
  {
    case TYPE_CROSS:
      return "+";
      break;
    case TYPE_CURVE_1:
      return "/";
      break;
    case TYPE_CURVE_2:
      return "\\";
      break;
  }
    return "fail";
}
/*
std::ostream &operator<<(std::ostream &out, const Tile &tile)
{
  tile.toStream(out);
  return out;
}
*/