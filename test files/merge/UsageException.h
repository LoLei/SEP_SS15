//------------------------------------------------------------------------------
// UsageException.h
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors:
// Verena Niederwanger 1430778
//------------------------------------------------------------------------------
//

#ifndef USAGE_H
#define USAGE_H

#include <exception>

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
