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

#include <stdexcept>
#include <iostream>

enum INDEX { x=0, y=1 ,X=0, Y=1 };

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
    Position(const Position &src) : x_(src.x_), y_(src.y_) {}
    virtual ~Position() throw();

    //--------------------------------------------------------------------------
    // Getter Methods
    //
    signed int getX();
    signed int getY();

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
    // von Vector2D mathoden
    //
    virtual Position &operator=(const Position&);
    virtual signed int &operator[](const INDEX) throw(std::range_error);

    virtual Position &operator+=(const Position&);
    virtual Position &operator-=(const Position&);
    virtual Position &operator*=(signed int);

    virtual Position operator+(const Position&) const;
    virtual Position operator-(const Position&) const;
    virtual Position operator-() const;
    virtual signed int operator*(const Position&) const; // scalar product
    virtual Position operator*(signed int) const;
    friend  Position operator*(signed int, const Position&);

    virtual bool operator==(const Position&) const;
    virtual bool operator!=(const Position&) const;
    
    virtual operator bool() const;    // true if non-zero

    friend std::istream& operator>>(std::istream&, Position&);
    friend std::ostream& operator<<(std::ostream&, const Position&);

};
#endif // POSITION_H
