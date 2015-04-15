#include <iostream>
#include <map>
#include "Position.h"

struct PositionPointerLesser : std::binary_function<Position*, Position*, bool>
{
  bool operator() (Position *lhs, Position *rhs) const
  {
    return *lhs < *rhs;  // This calls the operator < in your class
  }
};

int main()
{
  std::map<Position*, int, PositionPointerLesser> karte;
  Position p1;
  p1.setX(0);
  p1.setY(0);

  Position p2;
  p2.setX(0);
  p2.setY(1);

  Position p3;
  p3.setX(1);
  p3.setY(0);

  Position p4;
  p4.setX(1);
  p4.setY(1);

  karte.emplace(&p1, 1);
  karte.emplace(&p2, 2);
  karte.emplace(&p3, 3);
  karte.emplace(&p4, 4);

  

  for (auto& x : karte)
  {
    std::cout << x.first->toString() << ": " << x.second << std::endl;
  }
  return 0;
}