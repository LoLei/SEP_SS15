//------------------------------------------------------------------------------
// InvalidCoordinatesException.h
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
//------------------------------------------------------------------------------
//

#ifndef INVALIDCOORDINATES_H
#define INVALIDCOORDINATES_H

#include <exception>
#include <iostream>

//------------------------------------------------------------------------------
// InvalidCoordinatesException Class
// Class for error messages concerning invalid coordinates
//
class InvalidCoordinatesException : public std::exception
{
  private:
    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    InvalidCoordinatesException& operator=(const InvalidCoordinatesException& original);

  public:

    //--------------------------------------------------------------------------
    // Constructor
    // Constructs the exception
    //
    InvalidCoordinatesException();

    //--------------------------------------------------------------------------
    // Copy Constructor
    // Copies object
    //
    // @param the exception to be copied
    //
    InvalidCoordinatesException(InvalidCoordinatesException const &src);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~InvalidCoordinatesException() throw();

    //--------------------------------------------------------------------------
    // what method
    // Outputs error message
    //
    virtual const char *what() const throw();
};

#endif
