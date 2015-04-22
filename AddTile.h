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
#include <iostream>
#include <map>
#include <vector>
#include "Position.h"
#include "Tile.h"
#include "Command.h"
#include "Game.h"


class Addtile:public Command
{
  private:
    //Tile empty_tile(Tile::EMPTY_T,EMPTY_C);
  public:

    Addtile();
    //~Addtile();

    int execute(Game& board, std::vector<std::string>& params);

    bool valideInput(std::vector<std::string> user_input, Tile &tile, Position &position);

    bool abfrage(bool abfrage, bool &twisted, bool &lonely_tile, Tile &t1,
                 Color c1, Tile& t2);

    bool adaptTile(std::map<Position*, Tile*> karte, Tile &t1, Position p1);

    bool completeMap(std::map<Position*, Tile*> &karte,
                     std::vector<std::string> &forAddtile);

    void fillEmptyTiles(Game& board);
};

#endif //ADDTILE_H_INCLUDED

