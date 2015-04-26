//------------------------------------------------------------------------------
// NotConnectedFieldException.cpp
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
//------------------------------------------------------------------------------
//

#include "NotConnectedFieldException.h"

//------------------------------------------------------------------------------
NotConnectedFieldException::NotConnectedFieldException() : exception()
{
}

//------------------------------------------------------------------------------
NotConnectedFieldException::NotConnectedFieldException(NotConnectedFieldException const &src)
: exception(src)
{
}

//------------------------------------------------------------------------------
NotConnectedFieldException::~NotConnectedFieldException() throw()
{
}

//------------------------------------------------------------------------------
const char *NotConnectedFieldException::what() const throw()
{
  return "Invalid coordinates - field not connected to tile";
}
