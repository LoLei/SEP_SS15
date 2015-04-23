//------------------------------------------------------------------------------
// OutOfMemoryException.h
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors:
// Verena Niederwanger 1430778
//------------------------------------------------------------------------------
//

#ifndef OUTOFMEMORY_H
#define OUTOFMEMORY_H

#include <exception>
#include <iostream>

//------------------------------------------------------------------------------
// OutOfMemoryException Class
// Class for error messages concerning memory errors
//
class OutOfMemoryException : public std::exception
{
  private:
    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    OutOfMemoryException& operator=(const OutOfMemoryException& original);

  public:
    //--------------------------------------------------------------------------
    // Constructor
    // Constructs the excpeption
    //
    OutOfMemoryException();

    //--------------------------------------------------------------------------
    // Copy Constructor
    // Copies object
    //
    // @param the exception to be copied
    //
    OutOfMemoryException(OutOfMemoryException const &src);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~OutOfMemoryException() throw();

    //--------------------------------------------------------------------------
    // what method
    // Outputs error message
    //
    virtual const char *what() const throw();
};

#endif
