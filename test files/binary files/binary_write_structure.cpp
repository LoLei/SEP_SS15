#include <iostream>
#include <string>
#include <fstream>

int main()
{
  std::ofstream file("user_info.bin",
    std::ios::app | std::ios::out | std::ios::binary);
  std::cout << "Enter your name, your age and your money" << std::endl;
  std::cout << "Type quit to end program" << std::endl;

  std::string name;
  int age;
  float money;

  while (1)
  {
    std::cin >> name;
    if (name == "quit")
    {
      break;
    }
    std::cin >> age;
    std::cin >> money;
    file << name << ' ' << age << ' ' << money << std::endl;
  }

  file.close();
  return 0;
}