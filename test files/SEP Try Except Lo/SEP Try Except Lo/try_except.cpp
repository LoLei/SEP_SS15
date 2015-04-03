#include <iostream>
#include <exception>

int main()
{
  class MyException : public std::exception
  {
    virtual const char* what() const throw()
    {
      return "My exception happened";
    }
  };

  MyException myex;

  try
  {
    float age_mom;
    float age_kid;
    int test = 1;

    std::cout << "We're going to divide your mom's age by your age" << std::endl;
    std::cout << "Enter your mom's age and your age" << std::endl << std::endl;
    std::cin >> age_mom >> age_kid;

    // Kid older than mom
    if (age_kid > age_mom)
    {
      throw 1;
    }
    // Kid's age is 0, can't divide by 0
    if (age_kid == 0)
    {
      throw 2;
    }
    if (test == 1)
    {
      throw myex;
    }

    // No exception caught
    std::cout << "The result is: " << age_mom / age_kid << std::endl;

  }
  catch (int x)
  {
    if (x == 1)
    {
      std::cout << "You cannot be older than your mom. Error code: " << x << std::endl;
    }
    if (x == 2)
    {
      std::cout << "Can't divide by 0. Error Code: " << x << std::endl;
    }
  }
  catch (std::exception& e)
  {
    std::cout << e.what() << '\n';
  }
}