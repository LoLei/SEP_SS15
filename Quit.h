//------------------------------------------------------------------------------
// Filename: AddTile.h
// Description: ...
// Authors: Pichler
// Tutor: Philipp Loibl
// Group: 11574
// Created: 01.04.2015
// Last change: 01.04.2015
//------------------------------------------------------------------------------

#ifndef QUIT_H_INCLUDED
#define QUIT_H_INCLUDED

#include <string>
#include <vector>
#include "Position.h"
#include "Command.h"
#include "Game.h"


class Quit:public Command
{
  public:
    Quit();

    int execute(Game& board, std::vector<std::string>& params);

  //private:
  //  ~Quit();
};

#endif //QUIT_H_INCLUDED

