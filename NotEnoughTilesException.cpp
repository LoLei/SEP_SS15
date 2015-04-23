//------------------------------------------------------------------------------
// NotEnoughTilesException.cpp
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors: 
// Verena Niederwanger 1430778
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
