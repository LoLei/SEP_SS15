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
Tile::Tile(Type side, Color topcolor)
{
  side_ = side;
  topcolor_ = topcolor;
  of_activeplayer_ = EMPTY_C;
  white_id_ = 0;
  red_id_ = 0;
  move_ = 0;
}

Tile::Tile(Color top, Color right, Color bottom, Color left)
{
  move_ = 0;
  white_id_ = 0;
  red_id_ = 0;
  if((top == bottom && top != EMPTY_C) || (left == right && left != EMPTY_C))
  {
    side_ = TYPE_CROSS;
    if(top == EMPTY_C)
    {
      top = bottom;
    }
    else if(bottom == EMPTY_C)
    {
      bottom = top;
    }
    else if(left == EMPTY_C)
    {
      left = right;
    }
    else if(right == EMPTY_C)
    {
      right = left;
    }
    topcolor_ = top;
  }
  else if((top == left && top != EMPTY_C) || (right == bottom && right != EMPTY_C))
  {
    side_ = TYPE_CURVE_1;
    if(top == EMPTY_C)
    {
      top = left;
    }
    else if(bottom == EMPTY_C)
    {
      bottom = right;
    }
    else if(left == EMPTY_C)
    {
      left = top;
    }
    else if(right == EMPTY_C)
    {
      right = bottom;
    }
    topcolor_ = top;
  }
  else if((top == right && top != EMPTY_C) || (left == bottom && left != EMPTY_C))
  {
    side_ = TYPE_CURVE_2;
    if(top == EMPTY_C)
    {
      top = right;
    }
    else if(bottom == EMPTY_C)
    {
      bottom = left;
    }
    else if(left == EMPTY_C)
    {
      left = bottom;
    }
    else if(right == EMPTY_C)
    {
      right = top;
    }
    else topcolor_ = top;
  }
  else
  {
    side_ = EMPTY_T;
    topcolor_ = EMPTY_C;
  }
}

//------------------------------------------------------------------------------
Tile::Tile(const Tile & src)
{
  side_ = src.side_;
  topcolor_ = src.topcolor_;
  of_activeplayer_ = src.of_activeplayer_;
  white_id_ = src.white_id_;
  red_id_ = src.red_id_;
  move_ = src.move_;
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
void Tile::setPlayer(Color of_activeplayer)
{
  of_activeplayer_ = of_activeplayer;
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
Color Tile::getColor(int border)
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
  if(color == COLOR_RED)
  {
    return red_id_;
  }
  if(color == COLOR_WHITE)
  {
    return white_id_;
  }
  return 0;
}

//---------------------for Test cases----------
std::string Tile::getColorOut()
{
  switch (topcolor_)
  {
    case COLOR_WHITE:
      return "W";
      break;
    case COLOR_RED:
      return "R";
      break;
    case EMPTY_C:
      return "0";
      break;
  }
  return "fail";
}

std::string Tile::getPlayerColorOut()
{
  switch (of_activeplayer_)
  {
    case COLOR_WHITE:
      return "W";
      break;
    case COLOR_RED:
      return "R";
      break;
    case EMPTY_C:
      return "0";
      break;
  }
  return "fail";
}

int Tile::getPlayerColor()
{
  switch (of_activeplayer_)
  {
  case COLOR_WHITE:
    return 1;
    break;
  case COLOR_RED:
    return 2;
    break;
  case EMPTY_C:
    return 0;
    break;
  }
  return -1;
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
    case EMPTY_T:
      return "0";
      break;
  }
    return "fail";
}

char Tile::getTypeChar()
{
  switch (side_)
  {
  case TYPE_CROSS:
    return '+';
    break;
  case TYPE_CURVE_1:
    return '/';
    break;
  case TYPE_CURVE_2:
    return '\\';
    break;
  case EMPTY_T:
    return '0';
    break;
  }
  return 'f';
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
  if(topcolor_ == COLOR_RED)
  {
    return COLOR_WHITE;
  }
  if(topcolor_ == COLOR_WHITE)
  {
    return COLOR_RED;
  }
  else
  {
    return EMPTY_C;
  }
}

//------------------------------------------------------------------------------
Tile::Type Tile::charToType(char c)
{
  switch (c)
  {
    case '/':
      return TYPE_CURVE_1;
    case '+':
      return TYPE_CROSS;
    case '\\':
      return TYPE_CURVE_2;
    default:
      return EMPTY_T;
  }
}

//--------------------------------------------------------------------------------TODO
int Tile::oppositeBorder(int border)
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
  return 4;
}

//--------------------------------------------------------------------------------TODO
int Tile::getMove()
{
  return move_;
}

//--------------------------------------------------------------------------------TODO
void Tile::setMove(int move)
{
  move_ = move;
}