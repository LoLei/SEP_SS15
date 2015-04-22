//------------------------------------------------------------------------------
// WrongParameterException.h
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors:
// Verena Niederwanger 1430778
//------------------------------------------------------------------------------
//

#ifndef WRONGPARAMETER_H
#define WRONGPARAMETER_H

#include <exception>

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
