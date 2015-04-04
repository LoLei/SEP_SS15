#include "OutOfMemoryException.h"
#include <iostream>

OutOfMemoryException::OutOfMemoryException() : exception()
{
}

OutOfMemoryException::OutOfMemoryException(OutOfMemoryException const &src)
: exception(src)
{
}

OutOfMemoryException::~OutOfMemoryException() throw()
{
}

const char *OutOfMemoryException::what() const throw()
{
  return "Error: Out of Memory!";
  //std::cout << "Error: Out of Memory!" << std::endl;
}
