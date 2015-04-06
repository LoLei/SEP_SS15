#ifndef UNKNOWNCOMMAND_H
#define UNKNOWNCOMMAND_H

#include <exception>

class UnknownCommandException : public std::exception
{
public:
  UnknownCommandException();
  UnknownCommandException(UnknownCommandException const &src);
  virtual ~UnknownCommandException() throw();
  virtual const char *what() const throw();
};

#endif
