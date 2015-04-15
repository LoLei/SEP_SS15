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
#include "Position.h"
#include "Tile.h"
#include "Command.h"



class Addtile:public Command
{
  public:
    static signed int max_x_;
    static signed int max_y_;
    static signed int min_x_;
    static signed int min_y_;

    Addtile();
    //~Addtile();

    int execute(Game& board, std::vector<std::string>& params);
    bool valideInput(std::string user_input, Tile &tile, Position &position);
    void setMaximas(Position reference);
    void addNewTile(std::string user_input, std::map<Position*, Tile*> &karte,
                    int &tile_counter);
    bool abfrage(bool abfrage, bool &twisted, bool &lonely_tile, Tile &t1);
    bool adaptTile(std::map<Position*, Tile*> karte, Tile &t1, Position p1);

    bool completeMap(std::map<Position*, Tile*> &karte, int &tile_counter, 
                     std::string &forAddtile);
    void fillEmptyTiles(std::map<Position*, Tile*> &karte);
};

#endif //ADDTILE_H_INCLUDED

