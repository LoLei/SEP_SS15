//------------------------------------------------------------------------------
// UsageException.cpp
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors:
// Verena Niederwanger 1430778
//------------------------------------------------------------------------------
//

#include "UsageException.h"
#include <iostream>

//------------------------------------------------------------------------------
UsageException::UsageException() : exception()
{
}

//------------------------------------------------------------------------------
UsageException::UsageException(UsageException const &src)
: exception(src)
{
}

//------------------------------------------------------------------------------
UsageException::~UsageException() throw()
{
}

//------------------------------------------------------------------------------
const char *UsageException::what() const throw()
{
  return "Usage: <program>";
  //<programm> mit argv[0] ersetzen
}
