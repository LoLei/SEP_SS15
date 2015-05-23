//------------------------------------------------------------------------------
// Tile.cpp
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
//------------------------------------------------------------------------------
//

#include "Tile.h"

//------------------------------------------------------------------------------
Tile::Tile(Type side, Color topcolor) : side_(side), topcolor_(topcolor),
  white_id_(0), red_id_(0), move_(0)
{
}

//------------------------------------------------------------------------------
Tile::Tile(Color top, Color right, Color bottom, Color left) : side_(EMPTY_T),
  topcolor_(top), white_id_(0), red_id_(0), move_(0)
{
  if((top == bottom && top != EMPTY_C) ||
     (left == right && left != EMPTY_C))
  {
    side_ = TYPE_CROSS;
    if(topcolor_ != EMPTY_C)
    {
      return;
    }
    if((left != EMPTY_C || right != EMPTY_C))
    {
      if(left == COLOR_WHITE || right == COLOR_WHITE)
      {
        topcolor_ = COLOR_RED;
        return;
      }
      else if(left == COLOR_RED || right == COLOR_RED)
      {
        topcolor_ = COLOR_WHITE;
        return;
      }
    }
  }

  else if((top == left && top != EMPTY_C) ||
          (right == bottom && right != EMPTY_C))
  {
    side_ = TYPE_CURVE_1;
    if(topcolor_ != EMPTY_C)
    {
      return;
    }
    if((right != EMPTY_C || bottom != EMPTY_C))
    {
      if(right == COLOR_WHITE || bottom == COLOR_WHITE)
      {
        topcolor_ = COLOR_RED;
        return;
      }
      else if(right == COLOR_RED || bottom == COLOR_RED)
      {
        topcolor_ = COLOR_WHITE;
        return;
      }
    }
  }

  else if((top == right && top != EMPTY_C) ||
          (left == bottom && left != EMPTY_C))
  {
    side_ = TYPE_CURVE_2;
    if(topcolor_ != EMPTY_C)
    {
      return;
    }
    if((left != EMPTY_C || bottom != EMPTY_C))
    {
      if(left == COLOR_WHITE || bottom == COLOR_WHITE)
      {
        topcolor_ = COLOR_RED;
        return;
      }
      else if(left == COLOR_RED || bottom == COLOR_RED)
      {
        topcolor_ = COLOR_WHITE;
        return;
      }
    }
  }

  else
  {
    side_ = EMPTY_T;
    topcolor_ = EMPTY_C;
  }
}

//------------------------------------------------------------------------------
Tile::Tile(const Tile & src) : side_(src.side_), topcolor_(src.topcolor_),
  white_id_(src.white_id_), red_id_(src.red_id_), move_(src.move_)
{
}

//------------------------------------------------------------------------------
Tile::~Tile() throw()
{
}

//------------------------------------------------------------------------------
void Tile::setColor(Color topcolor)
{
  topcolor_ = topcolor;
}

//------------------------------------------------------------------------------
void Tile::setId(Color color, int id)
{
  if(color == COLOR_RED)
  {
    red_id_ = id;
  }
  if(color == COLOR_WHITE)
  {
    white_id_ = id;
  }
}

//------------------------------------------------------------------------------
Color Tile::getColor()
{
  return topcolor_;
}

//------------------------------------------------------------------------------
Color Tile::getColor(Border border)
{
  switch(border)
  {
    case TOP:
      return getColor();
    case RIGHT:
      switch (side_)
      {
        case TYPE_CROSS:  // +
          return notTopColor();
        case TYPE_CURVE_1:  // "/"
          return notTopColor();
        case TYPE_CURVE_2:  // "\"
          return topcolor_;
        default:
          return EMPTY_C;
      }
    case BOTTOM:
      switch (side_)
      {
        case TYPE_CROSS:  // +
          return topcolor_;
        case TYPE_CURVE_1:  // "/"
          return notTopColor();
        case TYPE_CURVE_2:  // "\"
          return notTopColor();
        default:
          return EMPTY_C;
      }
    case LEFT:
      switch (side_)
      {
        case TYPE_CROSS:  // +
          return notTopColor();
        case TYPE_CURVE_1:  // "/"
          return topcolor_;
        case TYPE_CURVE_2:  // "\"
          return notTopColor();
        default:
          return EMPTY_C;
      }
  }
  return EMPTY_C;
}

//------------------------------------------------------------------------------
char Tile::getTypeChar()
{
  switch (side_)
  {
    case TYPE_CROSS:
      return '+';
    case TYPE_CURVE_1:
      return '/';
    case TYPE_CURVE_2:
      return '\\';
    case EMPTY_T:
      return '0';
  }
    return '0';
}

//------------------------------------------------------------------------------
Tile::Type Tile::getType()
{
  return side_;
}

//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
int Tile::getId(Color color)
{
  switch (color)
  {
    case COLOR_WHITE:
      return white_id_;
    case COLOR_RED:
      return red_id_;
    case EMPTY_C:
      return 0;
  }
  return 0;
}

//------------------------------------------------------------------------------
Tile& Tile::operator=(const Tile& original)
{
  side_ = original.side_;
  topcolor_ = original.topcolor_;
  white_id_ = original.white_id_;
  red_id_ = original.red_id_;
  move_ = original.move_;
  return *this;
}

//------------------------------------------------------------------------------
bool Tile::operator==(const Tile &src) const
{
  return (side_ == src.side_ && topcolor_ == src.topcolor_);
}

//------------------------------------------------------------------------------
bool Tile::operator!=(const Tile &src) const
{
  return !(*this == src);
}

//------------------------------------------------------------------------------
Color Tile::notTopColor()
{
  switch (topcolor_)
  {
    case COLOR_WHITE:
      return COLOR_RED;
    case COLOR_RED:
      return COLOR_WHITE;
    case EMPTY_C:
      return EMPTY_C;
  }
  return EMPTY_C;
}

//------------------------------------------------------------------------------
Border Tile::oppositeBorder(Border border)
{
  switch(border)
  {
    case TOP:
      return BOTTOM;
    case RIGHT:
      return LEFT;
    case BOTTOM:
      return TOP;
    case LEFT:
      return RIGHT;
  }
}

//------------------------------------------------------------------------------
int Tile::getMove()
{
  return move_;
}

//------------------------------------------------------------------------------
void Tile::setMove(int move)
{
  move_ = move;
}