#ifndef WRONGPARAMETER_H
#define WRONGPARAMETER_H

#include <exception>

class WrongParameterException : public std::exception
{
  WrongParameterException();
  WrongParameterException(WrongParameterException const &src);
  virtual ~WrongParameterException() throw();
  virtual const char *what() const throw();
};

#endif