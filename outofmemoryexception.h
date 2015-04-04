#ifndef OUTOFMEMORY_H
#define OUTOFMEMORY_H

#include <exception>

class OutOfMemoryException : public std::exception
{
  OutOfMemoryException();
  OutOfMemoryException(OutOfMemoryException const &src);
  virtual ~OutOfMemoryException() throw();
  virtual const char *what() const throw();
};

#endif