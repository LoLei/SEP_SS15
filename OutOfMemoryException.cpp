//------------------------------------------------------------------------------
// OutOfMemoryException.cpp
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors:
// Verena Niederwanger 1430778
//------------------------------------------------------------------------------
//

#include "OutOfMemoryException.h"
#include <iostream>

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
