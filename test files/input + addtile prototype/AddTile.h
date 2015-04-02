//------------------------------------------------------------------------------
// Filename: AddTile.h
// Description: ...
// Authors: Pichler
// Tutor: Philipp Loibl
// Group: 11574
// Created: 01.04.2015
// Last change: 01.04.2015
//------------------------------------------------------------------------------

#ifndef ADDTILE_H_INCLUDED
#define ADDTILE_H_INCLUDED

#include <string>
#include <string>
#include <iostream>
#include "Position.h"
#include "Tile.h"
#include "Command.h"



class Addtile:public Command
{
  public:

    Addtile() : Command("Addtile"){};
    virtual ~Addtile();

    int execute(Game& board, std::vector<std::string>& params);

    bool valuecommand(std::string input, Tile &tile, Position &position, const Color color);
};

#endif //ADDTILE_H_INCLUDED

