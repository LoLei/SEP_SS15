//------------------------------------------------------------------------------
// UnknownCommandException.cpp
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors:
// Verena Niederwanger 1430778
//------------------------------------------------------------------------------
//

#include "UnknownCommandException.h"
#include <iostream>

//------------------------------------------------------------------------------
UnknownCommandException::UnknownCommandException() : exception()
{
}

//------------------------------------------------------------------------------
UnknownCommandException::UnknownCommandException(UnknownCommandException
  const &src) : exception(src)
{
}

//------------------------------------------------------------------------------
UnknownCommandException::~UnknownCommandException() throw()
{
}

//------------------------------------------------------------------------------
const char *UnknownCommandException::what() const throw()
{
  return "Error: Unknown command!";
}
