//------------------------------------------------------------------------------
// EmptyBoardException.h
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
//------------------------------------------------------------------------------
//

#ifndef EMPTYBOARD_H
#define EMPTYBOARD_H

#include <exception>
#include <iostream>

//------------------------------------------------------------------------------
// EmptyBoardException Class
// Class for error messages concerning an empty board
//
class EmptyBoardException : public std::exception
{
  private:
    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    EmptyBoardException& operator=(const EmptyBoardException& original);

  public:
    //--------------------------------------------------------------------------
    // Constructor
    // Constructs the exception
    //
    EmptyBoardException();

    //--------------------------------------------------------------------------
    // Copy Constructor
    // Copies object
    //
    // @param the exception to be copied
    //
    EmptyBoardException(EmptyBoardException const &src);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~EmptyBoardException() throw();

    //--------------------------------------------------------------------------
    // what method
    // Outputs error message
    //
    virtual const char *what() const throw();
};

#endif
