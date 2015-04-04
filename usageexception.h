#ifndef USAGE_H
#define USAGE_H

#include <exception>

class UsageException : public std::exception
{
  UsageException();
  UsageException(UsageException const &src);
  virtual ~UsageException() throw();
  virtual const char *what() const throw();
};

#endif