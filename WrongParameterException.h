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

#ifndef WRONGPARAMETER_H
#define WRONGPARAMETER_H

#include <exception>
#include <iostream>

//------------------------------------------------------------------------------
// WrongParameterException Class
// Class for error messages concerning parameter errors
//
class WrongParameterException : public std::exception
{
  private:
    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    WrongParameterException& operator=(const WrongParameterException& original);

  public:
    //--------------------------------------------------------------------------
    // Constructor
    // Constructs the excpeption
    //
    WrongParameterException();

    //--------------------------------------------------------------------------
    // Copy Constructor
    // Copies object
    //
    // @param the exception to be copied
    //
    WrongParameterException(WrongParameterException const &src);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~WrongParameterException() throw();

    //--------------------------------------------------------------------------
    // what method
    // Outputs error message
    //
    virtual const char *what() const throw();
};

#endif
