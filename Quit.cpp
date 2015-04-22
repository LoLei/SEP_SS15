//------------------------------------------------------------------------------
// Filename: Quit.cpp
// Description: ...
// Authors: Pichler
// Tutor: Philipp Loibl
// Group: 11574
// Created: 01.04.2015
// Last change: 01.04.2015
//------------------------------------------------------------------------------

#include "Quit.h"

//------------------------------------------------------------------------------
Quit::Quit() : Command("quit")
{
}

//------------------------------------------------------------------------------
int Quit::execute(Game& board, std::vector<std::string>& params)
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