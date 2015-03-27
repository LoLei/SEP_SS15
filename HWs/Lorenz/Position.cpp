#include "Position.h"
#include <string>
//#include <sstream>

Position::Position(int x, int y)
{
  x_ = x;
  y_ = y;
}

int Position::getX()
{
  return x_;
}

int Position::getY()
{
  return y_;
}

bool Position::parse(std::string input)
{
  // Delete two lines
  int x_;
  int y_;

  int new_x_int;
  int new_y_int;

  int i = 0;
  int k = 0;
  int h = 0;
  std::string new_x;
  std::string new_y;

  std::string to_parse;
  to_parse = input;

  while (1)
  {
    if (to_parse[i] == '(')
    {
      i++;
    }
    else
    {
      return false;
    }
    while (1)
    {
      if ((to_parse[i] >= 48) && (to_parse[i] <= 57) || (to_parse[i] == '-')
        || (to_parse[i] == '+'))
      {
        new_x = new_x + to_parse[i];
        if ((to_parse[i] == '-') || (to_parse[i] == '+'))
        {
          k = 1;
          i++;
          h = 1;
        }
        if (k == 1)
        {
          if ((to_parse[i] == '-') || (to_parse[i] == '+'))
          {
            return false;
          }
        }
        if (h == 0)
        {
          i++;
        }
        h = 0;
      }
      else if (to_parse[i] == ',')
      {
        i++;
        break;
      }
      else
      {
        return false;
      }
    }
    k = 0;
    while (1)
    {
      if ((to_parse[i] >= 48) && (to_parse[i] <= 57) || (to_parse[i] == '-')
        || (to_parse[i] == '+'))
      {
        new_y = new_y + to_parse[i];
        if ((to_parse[i] == '-') || (to_parse[i] == '-'))
        {
          k = 1;
          i++;
          h = 1;
        }
        if (k == 1)
        {
          if ((to_parse[i] == '-') || (to_parse[i] == '+'))
          {
            return false;
          }
        }
        if (h == 0)
        {
          i++;
        }
        h = 0;
      }
      else if (to_parse[i] == ')')
      {
        i++;
        break;
      }
      else
      {
        return false;
      }
    }
    if (to_parse[i] == '\0')
    {
      break;
    }
    else
    {
      return false;
    }
  }

  x_ = std::stoi(new_x);
  y_ = std::stoi(new_y);

  return true;
}

std::string Position::toString()
{
  std::ostringstream output_1;
  output_1 << "(" << std::dec << x_ << "," << std::dec << y_ << ")";

  std::string output_2;
  output_2 = output_1.str();
  
  return output_2;
}