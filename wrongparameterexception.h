#ifndef WRONGPARAMETER_H
#define WRONGPARAMETER_H

#include <exception>

class WrongParameter : public std::exception
{
  WrongParameter();
  WrongParameter(WrongParameter const &src);
  virtual ~WrongParameter() throw();
  virtual const char *what() const throw();
};

#endif