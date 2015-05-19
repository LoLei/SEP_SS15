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

//#include "UsageException.h"


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
    Game trax;
    std::string flag;
    std::string filename;
    if(argc == 3 && argv[1][0] == '-' && (flag = argv[1]).size() == 2)
    {
      switch(flag[1])
      {
        case 'g':
          filename = argv[2];
          trax.setOutputFilename(filename);
          break;
        default:
          //throw UsageException();
          std::cout << "Usage: " << argv[0] << std::endl;
          return 2;
      }
    }
    else if(argc == 1)
    {
      trax.setOutputFilename("");
    }
    else if(argc != 1 && argc != 3)
    {
      //throw UsageException();
      std::cout << "Usage: " << argv[0] << std::endl;
      return 2;
    }

    trax.run();
  }
  //catch (UsageException& e1)
  //{
    //std::cout << e1.what() << argv[0] << std::endl;
    //return 2;
  //}
  //catch(...)
  //{
    //std::cout << "Error: Out of Memory!" << std::endl;
    //return 1;
  //}
  catch(std::bad_alloc& ba)
    {
      std::cout << "Error: Out of Memory!" << std::endl;
    }
  return 0;
}