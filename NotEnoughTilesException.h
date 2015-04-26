//------------------------------------------------------------------------------
// AddTile.cpp
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
//------------------------------------------------------------------------------
//

#ifndef NOTENOUGHTILES_H
#define NOTENOUGHTILES_H

#include <exception>
#include <iostream>

//------------------------------------------------------------------------------
// NotEnoughTilesException Class
// Class for error messages concerning not enough tiles
//
class NotEnoughTilesException : public std::exception
{
  private:
    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    NotEnoughTilesException& operator=(const NotEnoughTilesException& original);

  public:
    //--------------------------------------------------------------------------
    // Constructor
    // Constructs the exception
    //
    NotEnoughTilesException();

    //--------------------------------------------------------------------------
    // Copy Constructor
    // Copies object
    //
    // @param the exception to be copied
    //
    NotEnoughTilesException(NotEnoughTilesException const &src);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~NotEnoughTilesException() throw();

    //--------------------------------------------------------------------------
    // what method
    // Outputs error message
    //
    virtual const char *what() const throw();
};

#endif
