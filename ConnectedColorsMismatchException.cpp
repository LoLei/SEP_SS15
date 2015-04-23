//------------------------------------------------------------------------------
// ConnectedColorsMismatchException.cpp
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors: 
// Verena Niederwanger 1430778
//------------------------------------------------------------------------------
//
#include "ConnectedColorsMismatchException.h"

//------------------------------------------------------------------------------
ConnectedColorsMismatchException::ConnectedColorsMismatchException() : exception()
{
}

//------------------------------------------------------------------------------
ConnectedColorsMismatchException::ConnectedColorsMismatchException(ConnectedColorsMismatchException const &src)
: exception(src)
{
}

//------------------------------------------------------------------------------
ConnectedColorsMismatchException::~ConnectedColorsMismatchException() throw()
{
}

//------------------------------------------------------------------------------
const char *ConnectedColorsMismatchException::what() const throw()
{
  return "Invalid move - connected line colors mismatch";
}
