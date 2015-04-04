#include "UnknownCommandException.h"
#include <iostream>

UnknownCommandException::UnknownCommandException() : exception()
{
}

UnknownCommandException::UnknownCommandException(UnknownCommandException const &src)
: exception(src)
{
}

UnknownCommandException::~UnknownCommandException() throw()
{
}

const char *UnknownCommandException::what() const throw()
{
  return "Error: Unknown command!";
  //std::cout << "Error: Unknown command!" << std::endl;
}
