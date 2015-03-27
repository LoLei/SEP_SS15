#ifndef POSITION_H
#define POSITION_H
#include "Tile.h"
#include <string>

class Position
{
private:
  int x_;
  int y_;
public:
  Position(int x, int y);
  int getX();
  int getY();
  bool parse(std::string input);
  std::string toString();
};

#endif