//------------------------------------------------------------------------------
// InvalidParameterException.cpp
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors: 
// Verena Niederwanger 1430778
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
