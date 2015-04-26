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

#ifndef USAGE_H
#define USAGE_H

#include <exception>
#include <iostream>

//------------------------------------------------------------------------------
// UsageException Class
// Class for error messages concerning usage errors
//
class UsageException : public std::exception
{
  private:
    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    UsageException& operator=(const UsageException& original);

  public:
    //--------------------------------------------------------------------------
    // Constructor
    // Constructs the excpeption
    //
    UsageException();

    //--------------------------------------------------------------------------
    // Copy Constructor
    // Copies object
    //
    // @param the exception to be copied
    //
    UsageException(UsageException const &src);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~UsageException() throw();

    //--------------------------------------------------------------------------
    // what method
    // Outputs error message
    //
    virtual const char *what() const throw();
};

#endif
