//------------------------------------------------------------------------------
// UnknownCommandException.h
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
//------------------------------------------------------------------------------
//

#ifndef UNKNOWNCOMMAND_H
#define UNKNOWNCOMMAND_H

#include <exception>
#include <iostream>

//------------------------------------------------------------------------------
// UnknownCommandException Class
// Class for error messages concerning unkown commands
//
class UnknownCommandException : public std::exception
{
  private:
    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    UnknownCommandException& operator=(const UnknownCommandException& original);

  public:
    //--------------------------------------------------------------------------
    // Constructor
    // Constructs the excpeption
    //
    UnknownCommandException();

    //--------------------------------------------------------------------------
    // Copy Constructor
    // Copies object
    //
    // @param the exception to be copied
    //
    UnknownCommandException(UnknownCommandException const &src);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~UnknownCommandException() throw();

    //--------------------------------------------------------------------------
    // what method
    // Outputs error message
    //
    virtual const char *what() const throw();
};

#endif
