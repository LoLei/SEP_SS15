#include "writeexception.h"
#include <iostream>


Writeexception::Writeexception() : exception()
{
}

Writeexception::Writeexception(Writeexception const &src)
: exception(src)
{
}

Writeexception::~Writeexception() throw()
{
}

const char *Writeexception::what() const throw()
{
  return "Cannot write file <filename>";
  //<filename> durch Parameter Filename ersetzen
}
