//------------------------------------------------------------------------------
// Filename: Write.h
// Description: Used for writing binary file
// Authors: Lorenz Leitner
// Tutor: Philipp Loibl
// Group: 11574
// Created: 14.04.2015
// Last change: 14.04.2015
//------------------------------------------------------------------------------

#ifndef WRITE_H_INCLUDED
#define WRITE_H_INCLUDED

#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include "Position.h"
#include "Tile.h"
#include "Command.h"
#include "Game.h"
#include "WriteException.h"
#include "Karte.h"

class Write :public Command
{
public:

  Write();
  //~Write();

  int execute(Game& board, std::vector<std::string>& params);

  void createNewFile(std::string user_input, std::map<Position*, Tile*> &karte,
    int &tile_counter);

  /*void togglePlayerWrite(FileHeader file_header);*/
};

#endif //WRITE_H_INCLUDED

