#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>


int main()
{
  char input[100];
  strcpy(input, "Testing");

  std::fstream file("test.bin",
    std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);

  if(!file.is_open())
  {
    std::cout << "error while opening the file" << std::endl;
  }
  else
  {
    int length = strlen(input);
    for (int i = 0; i <= length; i++)
    {
      file.put(input[i]);
    }
    file.seekg(0);
    char ch;
    while(file.good())
    {
      file.get(ch);
      std::cout << ch;
    }
  }

  file.close();

  return 0;
}
