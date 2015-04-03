#include <exception>

class BrickException : public std::exception
{
  virtual const char* what() const throw()
  {
    return "Brick happened";
  }
};

class WriteException : public std::exception
{
public:
  virtual const char* what() const throw()
  {
    return "Could not write";
  }
};

class NullDivision : public std::exception
{
  virtual const char* what() const throw()
  {
    return "Cannot divide by zero";
  }
};

class LogicalIntegrity : public std::exception
{
  virtual const char* what() const throw()
  {
    return "Kid cannot be older than mom";
  }
};