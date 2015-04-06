//------------------------------------------------------------------------------
// 4_zerodivideexception.cpp
//
// 
// Authors: Frank Kappe
//          Christian Safran
//------------------------------------------------------------------------------
//

#include "4_zerodivideexception.h"
#include <iostream>

ZeroDivideException::ZeroDivideException() : exception()
{
  std::cout << "ZeroDivideException: Constructor called" << std::endl;
}

ZeroDivideException::ZeroDivideException(ZeroDivideException const &src)
  : exception(src)
{
  std::cout << "ZeroDivideException: Copy-Constructor called" << std::endl;
}

ZeroDivideException::~ZeroDivideException() throw()
{
  std::cout << "ZeroDivideException: Destructor called" << std::endl;
}

const char *ZeroDivideException::what() const throw()
{
  return "Division By Zero Error";
}