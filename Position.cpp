//------------------------------------------------------------------------------
// Position.cpp
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
//------------------------------------------------------------------------------
//

#include "Position.h"

using std::string;

//------------------------------------------------------------------------------
Position::Position(signed int x, signed int y) : x_(x), y_(y)
{
}

//------------------------------------------------------------------------------
Position::Position() : x_(0), y_(0)
{
}

//------------------------------------------------------------------------------
Position::Position(const Position &original) : x_(original.x_), y_(original.y_)
{
}

//------------------------------------------------------------------------------
Position::~Position() throw()
{
}

//------------------------------------------------------------------------------
signed int Position::getX()
{
  return x_;
}

//------------------------------------------------------------------------------
signed int Position::getY()
{
  return y_;
}

//------------------------------------------------------------------------------
void Position::setX(const signed int x)
{
  x_ = x;
}

//------------------------------------------------------------------------------
void Position::setY(const signed int y)
{
  y_ = y;
}

//------------------------------------------------------------------------------
bool Position::parse(const string input)
{
  int string_size = input.size();
  if(input[0] == '(' && input[string_size-1] == ')'
     && input.find(",") != string::npos)
  {
    int coomma_index = input.find(",");
    string string_x = input.substr(1,coomma_index-1);
    string string_y = input.substr(coomma_index+1,string_size-coomma_index);
    try
    {
      x_ = std::stoi(string_x,nullptr);
      y_ = std::stoi(string_y,nullptr);
    }
    catch (const std::invalid_argument &ia)
    {
      return false;
    }
  }
  else
  {
    return false;
  }
  return true;
}

//------------------------------------------------------------------------------
const string Position::toString()
{
  string output = "(" + std::to_string(x_) + "," + std::to_string(y_) + ")";
  return output;
}

//------------------------------------------------------------------------------
Position &Position::operator=(const Position &position)
{
  x_ = position.x_;
  y_ = position.y_;
  return *this;
}

//------------------------------------------------------------------------------
bool Position::operator==(const Position &position) const
{
  return (x_ == position.x_ && y_ == position.y_);
}

//------------------------------------------------------------------------------
bool Position::operator!=(const Position &position) const
{
  return !(*this == position);
}

//------------------------------------------------------------------------------
bool Position::operator<(const Position &position) const
{
  if((x_ < position.x_) && (y_ == position.y_))
  {
    return true;
  }
  if(x_ > position.x_ && y_ < position.y_)
  {
    return true;
  }
  if(x_ == position.x_ && y_ < position.y_)
  {
    return true;
  }
  else
  {
    return false;
  }
}

//------------------------------------------------------------------------------
Position Position::getNearbyPosition(Border border)
{
  switch(border)
  {
    case TOP:
      return Position(x_,y_ - 1);
    case RIGHT:
      return Position(x_ + 1,y_);
    case BOTTOM:
      return Position(x_,y_ + 1);
    case LEFT:
      return Position(x_ - 1,y_);
  }
  return Position(0,0);
}
