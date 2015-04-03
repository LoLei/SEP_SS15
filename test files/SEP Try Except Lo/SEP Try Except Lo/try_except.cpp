#include <iostream>
#include "Customexceptions.h"

int main()
{
  try
  {
    float age_mom;
    float age_kid;
    int test = 2;

    std::cout << "We're going to divide your mom's age by your age" << std::endl;
    std::cout << "Enter your mom's age and your age" << std::endl << std::endl;
    std::cin >> age_mom >> age_kid;

    // Kid older than mom
    if (age_kid > age_mom)
    {
      throw LogicalIntegrity();
    }
    // Kid's age is 0, can't divide by 0
    if (age_kid == 0)
    {
      throw NullDivision();
    }
    if (test == 1)
    {
      throw BrickException();
    }
    if (test == 2)
    {
      throw WriteException();
    }

    // No exception caught
    std::cout << "The result is: " << age_mom / age_kid << std::endl;

  }
  catch (WriteException& e1)
  {
    std::cout << e1.what() << ' ' << "<file_name>" << std::endl;
  }
  catch (std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }
}