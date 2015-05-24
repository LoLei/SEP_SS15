//------------------------------------------------------------------------------
// Position.h
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
//------------------------------------------------------------------------------
//

#ifndef POSITION_H
#define POSITION_H

#include "Border.h"
#include <string>
#include <exception>
#include <stdexcept>

//------------------------------------------------------------------------------
// Position Class
// Class for positions containing x and y coordinates
//
class Position
{
  private:

    //--------------------------------------------------------------------------
    // x-coordinate
    //
    signed int x_;

    //--------------------------------------------------------------------------
    // y-coordinate
    //
    signed int y_;

  public:
    //--------------------------------------------------------------------------
    // Default constructor method
    //
    Position();

    //--------------------------------------------------------------------------
    // Constructor method
    //
    // @param x the x coordinate
    // @param y the y coordinate
    //
    Position(signed int x, signed int y);

    //--------------------------------------------------------------------------
    // Copy constructor
    // copies a position to a new position
    //
    // @param the position to be copied
    //
    Position(const Position &original);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Position() throw();

    //--------------------------------------------------------------------------
    // Getter Methods
    //
    signed int getX();
    signed int getY();

    //--------------------------------------------------------------------------
    // Setter Methods
    //
    void setX(const signed int x);
    void setY(const signed int y);

    //--------------------------------------------------------------------------
    // parse method
    // parses a string to a position
    //
    // @param input the string to be parsed
    //
    // @return bool true if it worked
    //
    bool parse(std::string input);

    //--------------------------------------------------------------------------
    // toString method
    // parses a position into a string
    //
    // @return std::string the position in a string
    //
    const std::string toString();

    //--------------------------------------------------------------------------
    // getNearbyPosition method
    // returns the position on the passed border
    //
    // @return Position on the passed border
    //
    Position getNearbyPosition(Border border);

    //--------------------------------------------------------------------------
    // operator Methods
    //

    //--------------------------------------------------------------------------
    // operator= method
    // Used to create one position from another
    //
    // @param position the position to take as source
    //
    // @return Position this the new position
    //
    virtual Position &operator=(const Position&);

    //--------------------------------------------------------------------------
    // operator== method
    // Used to compare two positions on equality
    //
    // @param Position the position with which the other position
    //        is to be compared
    //
    // @return bool true if position matches
    //
    virtual bool operator==(const Position&) const;

    //--------------------------------------------------------------------------
    // operator!= method
    // Used to compare two positions on inequality
    //
    // @param Position the position with which the other position
    //        is to be compared
    //
    // @return bool false if position matches
    //
    virtual bool operator!=(const Position&) const;

    //--------------------------------------------------------------------------
    // operator< method
    // Used to compare two positions on coordinates size
    // Used as custom comparator for sorted maps which use positions as key
    //
    // @param Position the position with which the other position
    //        is to be compared
    //
    // @return bool true if position is greater (if position is either right of
    //         other position or below other position)
    //
    virtual bool operator<(const Position&) const;
};
#endif // POSITION_H