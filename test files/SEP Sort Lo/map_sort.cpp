#include <iostream>
#include <string>
#include <map>
#include "CustomComp.h"

int main()
{
  std::map<std::string, int, cmpByStringLength> myMap;
  myMap.emplace("String 1", 5);
  myMap.emplace("String 123", 10);

  // Working
  for (std::map<std::string, int, cmpByStringLength>::iterator it = myMap.begin(); it != myMap.end(); ++it)
  {
    std::cout << it->first << " => " << it->second << std::endl;
  }
  return 0;
}