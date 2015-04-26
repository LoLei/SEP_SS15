//------------------------------------------------------------------------------
// main.cpp
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
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
  try
  {
    std::string file_name = "outputfile";
    int graphic_mode = 0;
    std::string flag;
    if(argc == 3 && argv[1][0] == '-' && (flag = argv[1]).size() == 2)
    {
      switch(argv[1][1])
      {
        case 'g':
          graphic_mode = 1;
          file_name = argv[2];
          break;
        default:
          throw UsageException();
      }
    }
    else if(argc != 1 && argc != 3)
    {
      throw UsageException();
    }

    Game trax;
    trax.run(file_name, graphic_mode);
  }
  catch (UsageException& e1)
  {
    std::cout << e1.what() << argv[0] << std::endl;
    return 2;
  }
  catch(...)
  {
    std::cout << "Error: Out of Memory!" << std::endl;
    return 1;
  }
  return 0;
}