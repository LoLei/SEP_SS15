//------------------------------------------------------------------------------
// ConnectedColorsMismatchException.h
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
//------------------------------------------------------------------------------
//

#ifndef CONNECTEDCOLORSMISMATCH_H
#define CONNECTEDCOLORSMISMATCH_H

#include <exception>
#include <iostream>

//------------------------------------------------------------------------------
// ConnectedColorsMismatchException Class
// Class for error messages concerning connected colors mismatch
//
class ConnectedColorsMismatchException : public std::exception
{
  private:
    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    ConnectedColorsMismatchException& operator=(const ConnectedColorsMismatchException& original);


  public:
    //--------------------------------------------------------------------------
    // Constructor
    // Constructs the exception
    //
    ConnectedColorsMismatchException();

    //--------------------------------------------------------------------------
    // Copy Constructor
    // Copies object
    //
    // @param the exception to be copied
    //
    ConnectedColorsMismatchException(ConnectedColorsMismatchException const &src);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~ConnectedColorsMismatchException() throw();

    //--------------------------------------------------------------------------
    // what method
    // Outputs error message
    //
    virtual const char *what() const throw();
};

#endif
