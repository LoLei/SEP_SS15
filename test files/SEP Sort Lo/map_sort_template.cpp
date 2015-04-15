#include <iostream>
#include <string>
#include <map>
#include "CustomComp.h"



template <typename std::map<std::string, int, cmpByStringLength>>


int main()
{
  
  
  void funcOut(std::map<std::string, int, cmpByStringLength>& myMap)
  {
    for (auto& p : myMap)
    {
      std::cout << p.first << " => " << p.second << std::endl;
    }
  }
}