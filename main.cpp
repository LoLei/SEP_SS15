//------------------------------------------------------------------------------
// main.cpp
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors: 
// Lorenz Leitner 1430211
// Markus Pichler 1331070
//------------------------------------------------------------------------------
//

#include <iostream>
#include <string>
#include "Game.h"

//------------------------------------------------------------------------------
// main function
// entry point for execution
//
// @param argc argument count
// @param **argv argument values
//        first used as graphic mode flag
//        second used as file name
//
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