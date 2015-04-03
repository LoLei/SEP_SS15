#include "UnknownCommand.h"
#include <iostream>

UnknownCommand::UnknownCommand() : exception()
{
}

UnknownCommand::UnknownCommand(UnknownCommand const &src)
: exception(src)
{
}

UnknownCommand::~UnknownCommand() throw()
{
}

const char *UnknownCommand::what() const throw()
{
  std::cout << "Error: Unknown command!" << std::endl;
  //return?
}
