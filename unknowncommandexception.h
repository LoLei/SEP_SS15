#ifndef UNKNOWNCOMMAND_H
#define UNKNOWNCOMMAND_H

#include <exception>

class UnknownCommand : public std::exception
{
  UnknownCommand();
  UnknownCommand(UnknownCommand const &src);
  virtual ~UnknownCommand() throw();
  virtual const char *what() const throw();
};

#endif
