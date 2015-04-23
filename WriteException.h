//------------------------------------------------------------------------------
// WriteException.h
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner 1430211
// Verena Niederwanger 1430778
//------------------------------------------------------------------------------
//

#ifndef WRITEEXCEPTION_H
#define WRITEEXCEPTION_H

#include <exception>
#include <string>

//------------------------------------------------------------------------------
// WriteException Class
// Class for error messages concerning write errors
//
class WriteException : public std::exception
{
  private:
    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    WriteException& operator=(const WriteException& original);

  public:
    //--------------------------------------------------------------------------
    // Constructor
    // Constructs the exception
    //
    WriteException();

    //--------------------------------------------------------------------------
    // Copy Constructor
    // Copies object
    //
    // @param the exception to be copied
    //
    WriteException(WriteException const &src);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~WriteException() throw();

    //--------------------------------------------------------------------------
    // what method
    // Outputs error message
    //
    virtual const char *what() const throw();
};

#endif
