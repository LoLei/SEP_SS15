//------------------------------------------------------------------------------
// 4_zerodivide_demo.cpp
//
// demonstrates nested exceptions
// 
// Authors: Frank Kappe
//          Christian Safran
//------------------------------------------------------------------------------
//

#include "4_zerodivideexception.h"
#include <iostream>

double quotient(int numerator, int denominator)
throw (ZeroDivideException)
{
  if (denominator == 0)
    throw ZeroDivideException();
  return static_cast<double>(numerator) / denominator;
}

double unsafeDivide(int a, int b) throw(ZeroDivideException)
{
  return quotient(a, b);
}

double safeDivide(int a, int b) throw()
{
  try
  {
    return quotient(a, b);
  }
  catch (ZeroDivideException &e)
  {
    std::cout << "safeDivide: " << e.what() << std::endl;
    std::cout << "returning zero as result" << std::endl;
    return 0.0;
  }
}

int main()
{
  try
  {
    int a = 1;
    int b = 0;
    std::cout << safeDivide(a, b) << std::endl;
    std::cout << unsafeDivide(a, b) << std::endl;
  }
  catch (std::exception &e)
  {
    std::cerr << "Main: " << e.what() << std::endl;
  }
}