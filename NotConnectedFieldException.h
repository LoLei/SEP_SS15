//------------------------------------------------------------------------------
// NotConnectedFieldException.h
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors:
// Verena Niederwanger 1430778
//------------------------------------------------------------------------------
//
#ifndef NOTCONNECTEDFIELD_H
#define NOTCONNECTEDFIELD_H

#include <exception>
#include <iostream>

//------------------------------------------------------------------------------
// NotConnectedFieldException Class
// Class for error messages concerning fields which are not connected
//
class NotConnectedFieldException : public std::exception
{
  private:
    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    NotConnectedFieldException& operator=(const NotConnectedFieldException& original);

  public:
    //--------------------------------------------------------------------------
    // Constructor
    // Constructs the exception
    //
    NotConnectedFieldException();

    //--------------------------------------------------------------------------
    // Copy Constructor
    // Copies object
    //
    // @param the exception to be copied
    //
    NotConnectedFieldException(NotConnectedFieldException const &src);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~NotConnectedFieldException() throw();

    //--------------------------------------------------------------------------
    // what method
    // Outputs error message
    //
    virtual const char *what() const throw();
};

#endif
