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

#include "EmptyBoardException.h"

//------------------------------------------------------------------------------
EmptyBoardException::EmptyBoardException() : exception()
{
}

//------------------------------------------------------------------------------
EmptyBoardException::EmptyBoardException(EmptyBoardException const &src)
: exception(src)
{
}

//------------------------------------------------------------------------------
EmptyBoardException::~EmptyBoardException() throw()
{
}

//------------------------------------------------------------------------------
const char *EmptyBoardException::what() const throw()
{
  return "Board is empty!";
}
