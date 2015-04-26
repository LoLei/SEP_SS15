//------------------------------------------------------------------------------
// AddTile.cpp
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
//------------------------------------------------------------------------------
//

#include "UsageException.h"

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
