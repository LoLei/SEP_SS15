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

#include "InvalidParameterException.h"

//------------------------------------------------------------------------------
InvalidParameterException::InvalidParameterException() : exception()
{
}

//------------------------------------------------------------------------------
InvalidParameterException::InvalidParameterException(InvalidParameterException const &src)
: exception(src)
{
}

//------------------------------------------------------------------------------
InvalidParameterException::~InvalidParameterException() throw()
{
}

//------------------------------------------------------------------------------
const char *InvalidParameterException::what() const throw()
{
  return "Invalid parameters!";
}
