//------------------------------------------------------------------------------
// NotConnectedFieldException.cpp
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors: 
// Verena Niederwanger 1430778
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
