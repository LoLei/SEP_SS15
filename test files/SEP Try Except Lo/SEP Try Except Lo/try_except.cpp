#include <iostream>

int main()
{
  try
  {
    int age_mom = 50;
    int age_son = 55;

    if (age_son > age_mom)
    {
      throw 99;
    }
    std::cout << "Success" << std::endl;
  }
  catch (int x)
  {
    std::cout << "Son cannot be older than mom. Error code: " << x << std::endl;
  }
  std::cout << "Test" << std::endl;
}