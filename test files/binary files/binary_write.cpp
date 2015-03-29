#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

int main()
{
  std::ofstream file("test2.bin",
    std::ios::out | std::ios::trunc | std::ios::binary);

  if (!file.is_open())
  {
    std::cout << "Cannot open file" << std::endl;
  }
  else
  {
    file << "This is a test." << std::endl;
    char num = 65;
    file << num << std::endl;
    file << static_cast<int>(num) << std::endl;
    file << "Test 2" << std::endl;
  }

  file.close();

  return 0;
}