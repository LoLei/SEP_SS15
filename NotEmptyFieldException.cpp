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

#include "NotEmptyFieldException.h"

//------------------------------------------------------------------------------
NotEmptyFieldException::NotEmptyFieldException() : exception()
{
}

//------------------------------------------------------------------------------
NotEmptyFieldException::NotEmptyFieldException(NotEmptyFieldException const &src)
: exception(src)
{
}

//------------------------------------------------------------------------------
NotEmptyFieldException::~NotEmptyFieldException() throw()
{
}

//------------------------------------------------------------------------------
const char *NotEmptyFieldException::what() const throw()
{
  return "Invalid coordinates - field not empty";
}
