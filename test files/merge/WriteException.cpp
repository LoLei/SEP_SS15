//------------------------------------------------------------------------------
// WriteException.cpp
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner 1430211
// Verena Niederwanger 1430778
//------------------------------------------------------------------------------
//

#include "WriteException.h"
#include <iostream>

//------------------------------------------------------------------------------
WriteException::WriteException() : exception()
{
}

//------------------------------------------------------------------------------
WriteException::WriteException(WriteException const &src)
: exception(src)
{
}

//------------------------------------------------------------------------------
WriteException::~WriteException() throw()
{
}

//------------------------------------------------------------------------------
const char *WriteException::what() const throw()
{
  return "Cannot write file ";
}
