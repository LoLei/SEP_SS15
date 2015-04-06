#include "WrongParameterException.h"
#include <iostream>

WrongParameterException::WrongParameterException() : exception()
{
}

WrongParameterException::WrongParameterException(WrongParameterException const &src)
: exception(src)
{
}

WrongParameterException::~WrongParameterException() throw()
{
}

const char *WrongParameterException::what() const throw()
{
  return "Error: Wrong parameter count!";
  //std::cout << "Error: Wrong parameter count!" << std::endl;
}
