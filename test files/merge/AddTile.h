//------------------------------------------------------------------------------
// AddTile.cpp
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors:
// Markus Pichler 1331070
//------------------------------------------------------------------------------
//

#ifndef ADDTILE_H_INCLUDED
#define ADDTILE_H_INCLUDED

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "Command.h"
#include "Game.h"


class Tile;
class Position;

//------------------------------------------------------------------------------
// AddTile Class
// Class to add tiles
//
class AddTile:public Command
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    AddTile(const AddTile& original);

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    AddTile& operator=(const AddTile& original);

    //--------------------------------------------------------------------------
    // Private member empty tile
    //
    Tile* empty_tile_;

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    AddTile();

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~AddTile();

    //--------------------------------------------------------------------------
    // execute method
    // Executes command
    //
    // @param board the game board
    // @param user_input the input the user enters
    //
    // @return int 0 if everything worked
    //
    int execute(Game& board, std::vector<std::string>& params);

    //--------------------------------------------------------------------------
    // valideInput method
    // Checks if command is correct
    //
    // @param user_input the input the user enters
    // @param tile the current tile
    // @param position the current position
    //
    // @return bool true if everything worked
    //
    bool valideInput(std::vector<std::string> user_input, Tile &tile,
      Position &position);

    //--------------------------------------------------------------------------
    // abfrage method
    // Checks if move is correct
    //
    // @param abfrage if true starts query
    // @param twisted if tile is twisted
    // @param lonely_tile if tile is placed not adjacent to two other tiles
    // @param tile the current tile
    //
    // @return bool true if everything worked
    //
    bool abfrage(bool abfrage, bool &twisted, bool &lonely_tile, Tile &t1,
                 Color c1, Tile& t2, std::vector<int> &red,
                 std::vector<int> &white);

    //--------------------------------------------------------------------------
    // adaptTile method
    // Turns tile so colors connect
    //
    // @param karte the game board of fields
    // @param tile the current tile
    // @param position the current position
    //
    // @return int 0 if everything worked 8 or 9 is somebody won
    //
    int adaptTile(std::map<Position*, Tile*> karte, Tile &t1, Position p1);

    //--------------------------------------------------------------------------
    // completeMap method
    // Fills map with forced tiles
    //
    // @param karte the game board of fields
    // @param forAddtile the new string to use as a command
    //
    // @return bool false if no tile needs to be force placed
    //
    bool completeMap(std::map<Position*, Tile*> &karte,
                     std::vector<std::string> &forAddtile);

    //--------------------------------------------------------------------------
    // fillEmptyTiles method
    // Fills map with empty tiles
    //
    // @param board the current board
    //
    void fillEmptyTiles(Game& board);

    //--------------------------------------------------------------------------
    // checkWin method
    // checks board if someone won
    //
    // @param board the current board
    //
    int checkWin(Game& board, Tile t1);
    int winLength(Game& board, Tile t1, std::string color);
};

#endif //ADDTILE_H_INCLUDED

