//------------------------------------------------------------------------------
// WrongParameterException.cpp
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
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
