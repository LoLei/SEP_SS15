#include "WrongParameter.h"
#include <iostream>

WrongParameter::WrongParameter() : exception()
{
}

WrongParameter::WrongParameter(WrongParameter const &src)
: exception(src)
{
}

WrongParameter::~WrongParameter() throw()
{
}

const char *WrongParameter::what() const throw()
{
  std::cout << "Error: Wrong parameter count!" << std::endl;
  //return?
}
