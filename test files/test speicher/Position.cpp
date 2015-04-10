//------------------------------------------------------------------------------
// Position.cpp
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors: Markus Pichler 1331070
// 
//------------------------------------------------------------------------------
//

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include "Position.h"

using std::string;
using std::cout;
using std::endl;

//------------------------------------------------------------------------------
Position::Position(signed int x, signed int y)
{
  x_ = x;
  y_ = y;
}
Position::Position()
{
  x_ = 0;
  y_ = 0;
}

//------------------------------------------------------------------------------
signed int Position::getX()
{
  return x_;
}

signed int Position::getY()
{
  return y_;
}

//------------------------------------------------------------------------------
bool Position::parse(const string input)
{
  int string_size = input.size();
  if(input[0] == '(' && input[string_size-1] == ')' && input.find(",") != string::npos)
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
string Position::toString()
{
  string output = "(" + std::to_string(x_) + "," + std::to_string(y_) + ")";
  return output;
}

void Position::setX(const signed int x)
{
  x_ = x;
}

void Position::setY(const signed int y)
{
  y_ = y;
}




//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Position::~Position() throw()
{
}

Position &Position::operator=(const Position &position)
{
  x_ = position.x_;
  y_ = position.y_;
  return *this;
}

signed int &Position::operator[](const INDEX index) throw(std::range_error)
{
  switch (index)
  {
    case X :
      return x_;

    case Y :
      return y_;

    default:
      throw std::range_error("Position: index not in [x,y]");
  }
}


Position &Position::operator+=(const Position &position)
{
  x_ += position.x_;
  y_ += position.y_;
  return *this;
}

Position &Position::operator-=(const Position &position)
{
  x_ -= position.x_;
  y_ -= position.y_;
  return *this;
}

Position &Position::operator*=(signed int factor)
{
  x_ *= factor;
  y_ *= factor;
  return *this;
}

Position Position::operator+(const Position &position) const
{
  Position temp;
  temp.x_ = x_ + position.x_;
  temp.y_ = y_ + position.y_;
  return temp;  // by value!
}

Position Position::operator-(const Position &position) const
{
  Position temp(*this);
  temp -= position;
  return temp;  // by value!
}

Position Position::operator-() const  // unary -
{
  return Position(-x_, -y_); // by value
}

signed int Position::operator*(const Position &position) const
{
  return (x_ * position.x_ + y_ * position.y_);  // scalar product
}

Position Position::operator*(signed int factor) const
{
  return Position (x_ * factor, y_ * factor);  
}

Position operator*(signed int factor, const Position &position)
{
  return Position(factor * position.x_, factor * position.y_);  
}

bool Position::operator==(const Position &position) const
{
  return (x_ == position.x_ && y_ == position.y_);
}

bool Position::operator!=(const Position &position) const
{
  return !(*this == position);
}
  
Position::operator bool() const    // true if non-zero
{
  return (x_ != 0.0 || y_ != 0.0);
}

std::istream& operator>>(std::istream& in, Position& position)
{
  signed int x, y;
  in >> x >> y;
  if (in.good())
  {
    position.x_ = x;
    position.y_ = y;
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const Position& position)
{
  out << "(" << position.x_ << "," << position.y_ << ")";
  return out;
}
