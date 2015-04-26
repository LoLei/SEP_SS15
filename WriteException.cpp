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

#include "WriteException.h"

//------------------------------------------------------------------------------
WriteException::WriteException() : exception()
{
}

//------------------------------------------------------------------------------
WriteException::WriteException(WriteException const &src)
: exception(src)
{
}

//------------------------------------------------------------------------------
WriteException::~WriteException() throw()
{
}

//------------------------------------------------------------------------------
const char *WriteException::what() const throw()
{
  return "Cannot write file ";
}
