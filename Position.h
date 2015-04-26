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

#include <iostream>
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
    Position(const Position &src);// : x_(src.x_), y_(src.y_) {}

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Position() throw();

    //--------------------------------------------------------------------------
    // Getter Methods
    //

    //--------------------------------------------------------------------------
    // getX method
    // Gets the x coordinate of a position
    //
    // @return int x_
    //
    signed int getX();

    //--------------------------------------------------------------------------
    // getY method
    // Gets the y coordinate of a position
    //
    // @return int y_
    //
    signed int getY();

    //--------------------------------------------------------------------------
    // Setter Methods
    //

    //--------------------------------------------------------------------------
    // setX method
    // Sets the x coordinate of a position
    //
    // @param x the x coordinate
    //
    void setX(const signed int x);

    //--------------------------------------------------------------------------
    // setY method
    // Sets the y coordinate of a position
    //
    // @param y the y coordinate
    //
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
    std::string toString();

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