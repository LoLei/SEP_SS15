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

#ifndef NOTEMPTYFIELD_H
#define NOTEMPTYFIELD_H

#include <exception>
#include <iostream>

//------------------------------------------------------------------------------
// NotEmptyFieldException Class
// Class for error messages concerning not empty fields
//
class NotEmptyFieldException : public std::exception
{
  private:
    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    NotEmptyFieldException& operator=(const NotEmptyFieldException& original);

  public:
    //--------------------------------------------------------------------------
    // Constructor
    // Constructs the exception
    //
    NotEmptyFieldException();

    //--------------------------------------------------------------------------
    // Copy Constructor
    // Copies object
    //
    // @param the exception to be copied
    //
    NotEmptyFieldException(NotEmptyFieldException const &src);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~NotEmptyFieldException() throw();

    //--------------------------------------------------------------------------
    // what method
    // Outputs error message
    //
    virtual const char *what() const throw();
};

#endif
