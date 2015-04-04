#ifndef USAGE_H
#define USAGE_H

#include <exception>

class Usage : public std::exception
{
  Usage();
  Usage(Usage const &src);
  virtual ~Usage() throw();
  virtual const char *what() const throw();
};

#endif