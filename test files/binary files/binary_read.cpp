#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

int main()
{
  std::ifstream file("test3.bin",
    std::ios::in | std::ios::binary);


  if (!file.is_open())
  {
    std::cout << "Cannot open file" << std::endl;
  }
  else
  {
    // Read
    char c;
    while ((file >> c) && (c != '\0'))
    {
      std::cout << c;
    }
  }

  return 0;
}