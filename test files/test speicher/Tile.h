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
#include <iostream>

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
    Tile();
    Tile(const Tile &);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Tile() throw();

    //--------------------------------------------------------------------------
    // Setter Methods
    //
    void setColor(Color topcolor);
    void setType(char c);

    //--------------------------------------------------------------------------
    // Getter Methods
    //
    Color getColor();
    Type getType();
    Color getColorLeft();
    Color getColorRight();
    Color getColorTop();
    Color getColorButtom();

    //--------------------------------------------------------------------------
    // Get Output Methods
    //
    std::string getColorOut();
    std::string getTypeOut();

    //--------------------------------------------------------------------------
    // Operator Methods
    //
    virtual bool operator==(const Tile&) const;
    virtual bool operator!=(const Tile&) const;

    //--------------------------------------------------------------------------
    // return the color who isnt the topcolor
    //
    Color notTopColor();
};
#endif // TILE_H
