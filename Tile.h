//------------------------------------------------------------------------------
// Tile.h
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
//------------------------------------------------------------------------------
//

#ifndef TILE_H
#define TILE_H

#include "Color.h"
#include "Border.h"

//------------------------------------------------------------------------------
// Tile Class
// Class for tiles
//
class Tile
{

  public:
    //--------------------------------------------------------------------------
    // Type Enum
    // Enum for easier reading of tile types
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

    //--------------------------------------------------------------------------
    // int white Id to identify tile
    //
    int white_id_;

    //--------------------------------------------------------------------------
    // int red Id to identify tile
    //
    int red_id_;

    //--------------------------------------------------------------------------
    // int move to identify the move
    //
    int move_;

  public:
    //--------------------------------------------------------------------------
    // Constructor method
    //
    // @param side the type of tile
    // @param topcolor the top color
    //
    Tile(Type side, Color topcolor);

    //--------------------------------------------------------------------------
    // Copy constructor
    // copies a tile to a new tile
    //
    // @param original the tile to be copied
    //
    Tile(const Tile &original);

    //--------------------------------------------------------------------------
    // Constructor method
    //
    // @param top the top color
    // @param right the right color
    // @param bottom the bottom color
    // @param left the left color
    //
    Tile(Color top, Color right, Color bottom, Color left);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Tile() throw();

    //--------------------------------------------------------------------------
    // Setter Methods
    //
    void setColor(Color topcolor);
    void setMove(int move);

    //--------------------------------------------------------------------------
    // setType method
    // Sets the type of a tile
    //
    // @param char_side the type, either '+', '/' or '\'
    //
    void setType(char char_side);

    //--------------------------------------------------------------------------
    // setId method
    // Sets int(ID) of a tile
    //
    // @param id the int( ID) of a tile
    //
    void setId(Color color, int id);

    //--------------------------------------------------------------------------
    // Getter Methods
    //
    Type getType();
    int getMove();
    Color getColor();

    //--------------------------------------------------------------------------
    // getTypeChar method
    // Gets the char of the type of a tile
    //
    // @return Char converted side_
    //
    char getTypeChar();

    //--------------------------------------------------------------------------
    // getColor method
    // Gets the color of the tile on the passed border
    //
    // @param Border border of the tile
    //
    // @return Color of the passed border
    //
    Color getColor(Border border);

    //--------------------------------------------------------------------------
    // getId method
    // gets a color id of a tile
    //
    // @param Color color of the needed id
    //
    // @return int id of the color(depend on input)
    //
    int getId(Color color);

    //--------------------------------------------------------------------------
    // Operator Methods
    //

    //--------------------------------------------------------------------------
    // assignment operator
    virtual Tile& operator=(const Tile& original);

    //--------------------------------------------------------------------------
    // operator== method
    // Used to compare two tiles on equality
    //
    // @param Tile the tile with which the other tile is to be compared
    //
    // @return bool true if tile matches
    //
    virtual bool operator==(const Tile&) const;

    //--------------------------------------------------------------------------
    // operator!= method
    // Used to compare two tiles on inequality
    //
    // @param Tile the tile with which the other tile is to be compared
    //
    // @return bool true if tile does not match
    //
    virtual bool operator!=(const Tile&) const;

    //--------------------------------------------------------------------------
    // notTopColor method
    // Returns the color which is not the top color
    //
    // @return Color COLOR_WHITE if top color is red
    // @return Color COLOR_RED if top color is white
    // @return Color EMPTY_C if top color is empty
    //
    Color notTopColor();


    //--------------------------------------------------------------------------
    // oppositeBorder method
    // return Border the opposite border of the passed
    //
    // @param Border border the opposite border is searched
    //
    // @return Border TOP <-> BOTTOM or LEFT <->RIGHT
    //
    Border oppositeBorder(Border border);

};
#endif // TILE_H