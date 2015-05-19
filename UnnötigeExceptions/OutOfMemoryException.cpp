//------------------------------------------------------------------------------
// OutOfMemoryException.cpp
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
//------------------------------------------------------------------------------
//

#include "OutOfMemoryException.h"

//------------------------------------------------------------------------------
OutOfMemoryException::OutOfMemoryException() : exception()
{
}

//------------------------------------------------------------------------------
OutOfMemoryException::OutOfMemoryException(OutOfMemoryException const &src)
: exception(src)
{
}

//------------------------------------------------------------------------------
OutOfMemoryException::~OutOfMemoryException() throw()
{
}

//------------------------------------------------------------------------------
const char *OutOfMemoryException::what() const throw()
{
  return "Error: Out of Memory!";
}
