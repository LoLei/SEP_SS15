#ifndef OUTOFMEMORY_H
#define OUTOFMEMORY_H

#include <exception>

class OutOfMemory : public std::exception
{
  OutOfMemory();
  OutOfMemory(OutOfMemory const &src);
  virtual ~OutOfMemory() throw();
  virtual const char *what() const throw();
};

#endif