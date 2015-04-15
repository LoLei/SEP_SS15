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
      EMPTY_T = 0,
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
    // Constructor + copy
    //
    Tile(Type side, Color orientation);
    Tile(const Tile &);
    Tile(Color Li, Color Re, Color Ob, Color Un);

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
    Type getType();
    Color getColor();
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

    //--------------------------------------------------------------------------
    // return the type for the char
    //
    Type charToType(char c);

};
#endif // TILE_H