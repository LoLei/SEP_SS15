//------------------------------------------------------------------------------
// main.cpp
//
// Group: Group 43, study assistant: Max Mustertutor
//
// Authors: Super Student 1 (0800001)
// Super Student 2 (0800002)
// Super Student 3 (0800003)
// Super Student 4 (0800004)
//------------------------------------------------------------------------------
//

#include <iostream>
#include <string>
#include "Game.h"

//------------------------------------------------------------------------------
// main function
// entry point for execution
// @param argc argument count
// @param **argv argument values
// @return return value for the OS
//
int main(int argc, char **argv)
{
  std::string file_name = "outputfile";
  int graphic_mode = 0;
  if(argc == 3)

  {
    std::string flag = argv[1];
    if(flag == "-g")
    {
      graphic_mode = 1;
      file_name = argv[2];
      std::cout << " === GRAFIC MODE === " << std::endl;
    }
  }

  Game trax;
  std::cout << " === GAME === " << std::endl;
  trax.run(file_name, graphic_mode);
  return 0;
}