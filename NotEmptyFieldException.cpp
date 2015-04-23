//------------------------------------------------------------------------------
// NotEmptyFieldException.cpp
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors: 
// Verena Niederwanger 1430778
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
