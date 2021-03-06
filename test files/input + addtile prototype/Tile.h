//------------------------------------------------------------------------------
// Tile.h
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors: Markus Pichler 1331070
// 
//------------------------------------------------------------------------------
//

#ifndef TILE_H
#define TILE_H

#include "Color.h"
#include <string>

//------------------------------------------------------------------------------
// Tile Class
//
class Tile
{

  public:
    //--------------------------------------------------------------------------
    // enum Type
    //
    enum Type
    {
      TYPE_CROSS = 1,
      TYPE_CURVE_1 = 2,
      TYPE_CURVE_2 = 3
    };

  private:

    //--------------------------------------------------------------------------
    // Type of Tile
    //
    Type side_;

    //--------------------------------------------------------------------------
    // Color of the active Curve
    //
    Color topcolor_;

  public:

    //--------------------------------------------------------------------------
    // Constructor
    //
    Tile(Type side, Color topcolor);

    void setColor(Color topcolor);
    void setType(char c);

    Color getColor();
    Type getType();

    std::string getColorOut();
    std::string getTypeOut();

    Tile();
//    Tile(const Tile &);
//    ~Tile();
};
#endif // TILE_H
