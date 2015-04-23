//------------------------------------------------------------------------------
// InvalidCoordinatesException.h
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors:
// Verena Niederwanger 1430778
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
