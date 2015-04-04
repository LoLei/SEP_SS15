#ifndef WRITEEXCEPTION_H
#define WRITEEXCEPTION_H

#include <exception>

class Writeexception : public std::exception
{
public:
  Writeexception();
private:
  Writeexception(Writeexception const &src);
public:
  virtual ~Writeexception() throw();
  virtual const char *what() const throw();
};

#endif