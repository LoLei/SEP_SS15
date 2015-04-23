//------------------------------------------------------------------------------
// WrongParameterException.cpp
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors:
// Verena Niederwanger 1430778
//------------------------------------------------------------------------------
//

#include "WrongParameterException.h"

//------------------------------------------------------------------------------
WrongParameterException::WrongParameterException() : exception()
{
}

//------------------------------------------------------------------------------
WrongParameterException::WrongParameterException(WrongParameterException
  const &src) : exception(src)
{
}

//------------------------------------------------------------------------------
WrongParameterException::~WrongParameterException() throw()
{
}

//------------------------------------------------------------------------------
const char *WrongParameterException::what() const throw()
{
  return "Error: Wrong parameter count!";
}
