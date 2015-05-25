//------------------------------------------------------------------------------
// Quit.cpp
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
//------------------------------------------------------------------------------
//

#include "Quit.h"

//------------------------------------------------------------------------------
Quit::Quit() : Command("quit")
{
}

//------------------------------------------------------------------------------
Quit::~Quit()
{
}

//------------------------------------------------------------------------------
int Quit::execute(Game &board, std::vector<std::string> &params)
{
  if(params.size() != 1)
  {
    std::cout << "Error: Wrong parameter count!" << std::endl;
    return 1;
  }
  board.setRunning(false);
  std::cout << "Bye!" << std::endl;
  return 0;
}