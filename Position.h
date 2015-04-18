//------------------------------------------------------------------------------
// Position.h
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors: Markus Pichler 1331070
//
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
//
class Position
{
  private:

    //--------------------------------------------------------------------------
    // x- Koordinate
    //
    signed int x_;

    //--------------------------------------------------------------------------
    // y- Koordinate
    //
    signed int y_;

  public:

    //--------------------------------------------------------------------------
    // Constructor
    //
    Position();
    Position(signed int x, signed int y);
    Position(const Position &src);// : x_(src.x_), y_(src.y_) {}

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
    // parse Method
    //
    bool parse(std::string input);

    //--------------------------------------------------------------------------
    // toString Method
    //
    std::string toString();

    //--------------------------------------------------------------------------
    // operator Methods
    // von Vector2D
    virtual Position &operator=(const Position&);

    virtual bool operator==(const Position&) const;
    virtual bool operator!=(const Position&) const;
    virtual bool operator>(const Position&) const;
    virtual bool operator<(const Position&) const;
};
#endif // POSITION_H