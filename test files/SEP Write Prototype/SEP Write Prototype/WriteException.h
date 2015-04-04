#ifndef WRITEEXCEPTION_H
#define WRITEEXCEPTION_H

#include <exception>
#include <string>

class WriteException : public std::exception
{
public:
  WriteException();
  WriteException(WriteException const &src);
  virtual ~WriteException() throw();
  virtual const char *what() const throw();
};

#endif
