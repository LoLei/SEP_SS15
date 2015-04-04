#include "UsageException.h"
#include <iostream>

UsageException::UsageException() : exception()
{
}

UsageException::UsageException(UsageException const &src)
: exception(src)
{
}

UsageException::~UsageException() throw()
{
}

const char *UsageException::what() const throw()
{
  return "Usage: <program>";
  //std::cout << "Usage: " << "<program>" << std::endl;
  //<programm> mit argv[0] ersetzen
}
