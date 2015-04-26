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

#include "NotEnoughTilesException.h"

//------------------------------------------------------------------------------
NotEnoughTilesException::NotEnoughTilesException() : exception()
{
}

//------------------------------------------------------------------------------
NotEnoughTilesException::NotEnoughTilesException(NotEnoughTilesException const &src)
: exception(src)
{
}

//------------------------------------------------------------------------------
NotEnoughTilesException::~NotEnoughTilesException() throw()
{
}

//------------------------------------------------------------------------------
const char *NotEnoughTilesException::what() const throw()
{
  return "Invalid move - not enough tiles left";
}
