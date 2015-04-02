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
bool Position::parse(string input)
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