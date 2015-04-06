//------------------------------------------------------------------------------
// 4_zerodivideexception.h
//
// 
// Authors: Frank Kappe
//          Christian Safran
//------------------------------------------------------------------------------
//

#ifndef ZERODIVIDEEXCEPTION_H
#define ZERODIVIDEEXCEPTION_H

#include <exception>

class ZeroDivideException : public std::exception
{
public:
  ZeroDivideException();
  ZeroDivideException(ZeroDivideException const &src);
  virtual ~ZeroDivideException() throw();
  virtual const char *what() const throw();
};

#endif