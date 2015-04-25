//------------------------------------------------------------------------------
// Tile.cpp
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors:
// Markus Pichler 1331070
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
}

Tile::Tile(Color Li, Color Re, Color Ob, Color Un)
{
  if((Ob == Un && Ob != EMPTY_C) || (Li == Re && Li != EMPTY_C))
  {
    side_ = TYPE_CROSS;
    if(Ob == EMPTY_C)
    {
      Ob = Un;
    }
    else if(Un == EMPTY_C)
    {
      Un = Ob;
    }
    else if(Li == EMPTY_C)
    {
      Li = Re;
    }
    else if(Re == EMPTY_C)
    {
      Re = Li;
    }
    topcolor_ = Ob;
  }
  else if((Ob == Li && Ob != EMPTY_C) || (Re == Un && Re != EMPTY_C))
  {
    side_ = TYPE_CURVE_1;
    if(Ob == EMPTY_C)
    {
      Ob = Li;
    }
    else if(Un == EMPTY_C)
    {
      Un = Re;
    }
    else if(Li == EMPTY_C)
    {
      Li = Ob;
    }
    else if(Re == EMPTY_C)
    {
      Re = Un;
    }
    topcolor_ = Ob;
  }
  else if((Ob == Re && Ob != EMPTY_C) || (Li == Un && Li != EMPTY_C))
  {
    side_ = TYPE_CURVE_2;
    if(Ob == EMPTY_C)
    {
      Ob = Re;
    }
    else if(Un == EMPTY_C)
    {
      Un = Li;
    }
    else if(Li == EMPTY_C)
    {
      Li = Un;
    }
    else if(Re == EMPTY_C)
    {
      Re = Ob;
    }
    else topcolor_ = Ob;
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
void Tile::setRedId(int red_id)
{
  red_id_ = red_id;
}

//------------------------------------------------------------------------------
void Tile::setWhiteId(int white_id)
{
  white_id_ = white_id;
}

//------------------------------------------------------------------------------
Color Tile::getColor()
{
  return topcolor_;
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
int Tile::getId(std::string color)
{
  if(color == "red")
  {
    return red_id_;
  }
  if(color == "white")
  {
    return white_id_;
  }
  return 0;
}

//------------------------------------------------------------------------------
int Tile::getRedId()
{
  return red_id_;
}

//------------------------------------------------------------------------------
int Tile::getWhiteId()
{
  return white_id_;
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
//-----------------------------------

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
Color Tile::getColorLeft()
{
  switch (side_)
  {
    case TYPE_CROSS:  // +
      return notTopColor();
      break;
    case TYPE_CURVE_1:  // "/"
      return topcolor_;
      break;
    case TYPE_CURVE_2:  // "\"
      return notTopColor();
      break;
    default:
      return EMPTY_C;
  }
}

//------------------------------------------------------------------------------
Color Tile::getColorRight()
{
  switch (side_)
  {
    case TYPE_CROSS:  // +
      return notTopColor();
      break;
    case TYPE_CURVE_1:  // "/"
      return notTopColor();
      break;
    case TYPE_CURVE_2:  // "\"
      return topcolor_;
      break;
    default:
      return EMPTY_C;
  }
}

//------------------------------------------------------------------------------
Color Tile::getColorTop()
{
  return getColor();
}

//------------------------------------------------------------------------------
Color Tile::getColorButtom()
{
  switch (side_)
  {
    case TYPE_CROSS:  // +
      return topcolor_;
      break;
    case TYPE_CURVE_1:  // "/"
      return notTopColor();
      break;
    case TYPE_CURVE_2:  // "\"
      return notTopColor();
      break;
    default:
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