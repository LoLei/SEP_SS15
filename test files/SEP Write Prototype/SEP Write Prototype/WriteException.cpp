#include "WriteException.h"
#include <iostream>


WriteException::WriteException() : exception()
{
}

WriteException::WriteException(WriteException const &src)
: exception(src)
{
}

WriteException::~WriteException() throw()
{
}

const char *WriteException::what() const throw()
{
  return "Cannot write file ";
}
