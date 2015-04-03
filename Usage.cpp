#include "Usage.h"
#include <iostream>

Usage::Usage() : exception()
{
}

Usage::Usage(Usage const &src)
: exception(src)
{
}

Usage::~Usage() throw()
{
}

const char *Usage::what() const throw()
{
  std::cout << "Usage: " << "<program>" << std::endl;
  //<programm> mit argv[0] ersetzen
  //return?
}
