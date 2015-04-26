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
