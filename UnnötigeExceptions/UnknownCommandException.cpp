//------------------------------------------------------------------------------
// UnknownCommandException.cpp
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
//------------------------------------------------------------------------------
//

#include "UnknownCommandException.h"

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
