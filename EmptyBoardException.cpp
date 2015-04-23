//------------------------------------------------------------------------------
// EmptyBoardException.cpp
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors: 
// Verena Niederwanger 1430778
//------------------------------------------------------------------------------
//
#include "EmptyBoardException.h"

//------------------------------------------------------------------------------
EmptyBoardException::EmptyBoardException() : exception()
{
}

//------------------------------------------------------------------------------
EmptyBoardException::EmptyBoardException(EmptyBoardException const &src)
: exception(src)
{
}

//------------------------------------------------------------------------------
EmptyBoardException::~EmptyBoardException() throw()
{
}

//------------------------------------------------------------------------------
const char *EmptyBoardException::what() const throw()
{
  return "Board is empty!";
}
