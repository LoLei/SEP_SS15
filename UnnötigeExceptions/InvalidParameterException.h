//------------------------------------------------------------------------------
// InvalidParameterException.h
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
//------------------------------------------------------------------------------
//

#ifndef INVALIDPARAMETER_H
#define INVALIDPARAMETER_H

#include <exception>
#include <iostream>

//------------------------------------------------------------------------------
// InvalidParameterException Class
// Class for error messages concerning invalid Parameters
//
class InvalidParameterException : public std::exception
{
  private:
    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    InvalidParameterException& operator=(const InvalidParameterException& original);

  public:
    //--------------------------------------------------------------------------
    // Constructor
    // Constructs the exception
    //
    InvalidParameterException();

    //--------------------------------------------------------------------------
    // Copy Constructor
    // Copies object
    //
    // @param the exception to be copied
    //
    InvalidParameterException(InvalidParameterException const &src);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~InvalidParameterException() throw();

    //--------------------------------------------------------------------------
    // what method
    // Outputs error message
    //
    virtual const char *what() const throw();
};

#endif
