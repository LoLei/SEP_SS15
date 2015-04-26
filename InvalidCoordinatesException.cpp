//------------------------------------------------------------------------------
// InvalidCoordinatesException.cpp
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
//------------------------------------------------------------------------------
//

#include "InvalidCoordinatesException.h"

//------------------------------------------------------------------------------
InvalidCoordinatesException::InvalidCoordinatesException() : exception()
{
}

//------------------------------------------------------------------------------
InvalidCoordinatesException::InvalidCoordinatesException(InvalidCoordinatesException const &src)
: exception(src)
{
}

//------------------------------------------------------------------------------
InvalidCoordinatesException::~InvalidCoordinatesException() throw()
{
}

//------------------------------------------------------------------------------
const char *InvalidCoordinatesException::what() const throw()
{
  return "Invalid coordinates - first tile must be set on (0,0)";
}
