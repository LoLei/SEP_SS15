//------------------------------------------------------------------------------
// Karte.h
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors: 
// Lorenz Leitner 1430211
//------------------------------------------------------------------------------
//

#ifndef KARTE_H_INCLUDED
#define KARTE_H_INCLUDED

#include <string>
#include <iostream>
#include <map>
#include "Position.h"
#include "Tile.h"
#include "Command.h"

struct customKeyComparator : std::binary_function<Position*, Position*, bool>
{
  //--------------------------------------------------------------------------
  // operator() method
  // Used when map called with this comparator wants to sort keys
  // Calls operator< method from Position class to sort
  //
  // @param lhs Position to be sorted
  // @param rhs Position to be sorted
  //
  // @return bool true if position is greater (if position is either right of
  //         other position or below other position)
  //
  bool operator() (Position *lhs, Position *rhs) const
  {
    return *lhs < *rhs;  // This calls the operator < in your class
  }
};

//------------------------------------------------------------------------------
// Karte Class
// Class for sorting a map using the custom key comparator
//
class Karte
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    Karte(const Karte& original);

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    Karte& operator=(const Karte& original);

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    Karte();

    //--------------------------------------------------------------------------
    // Destructor
    //
    //~Addtile();
};

#endif //KARTE_H_INCLUDED

