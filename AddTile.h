//------------------------------------------------------------------------------
// AddTile.h
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
//------------------------------------------------------------------------------
//

#ifndef ADDTILE_H_INCLUDED
#define ADDTILE_H_INCLUDED

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <climits>


#include "Command.h"

class Game;
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

    static int id_counter_;

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

    //-------------------------------------------------------------------------- ------TODO
    // colorAndIdCheck method
    // Checks if move is correct
    //
    // @param abfrage if true starts query
    // @param twisted if tile is twisted
    // @param lonely_tile if tile is placed not adjacent to two other tiles
    // @param tile the current tile
    //
    // @return bool true if everything worked
    //
    bool colorCheck(bool color_bool, bool &twisted, bool &lonely_tile,
                         Tile &current_tile);

    //-------------------------------------------------------------------------- -------TODO
    // adaptTile method
    // Turns tile so colors connect
    //
    // @param field the game board of fields
    // @param tile the current tile
    // @param position the current position
    //
    // @return int 0 if everything worked 8 or 9 is somebody won
    //
    int adaptTile(std::map<Position*, Tile*> field, Tile &current_tile, Position current_position);

    //--------------------------------------------------------------------------
    // completeMap method
    // Fills map with forced tiles
    //
    // @param field the game board of fields
    // @param forAddtile the new string to use as a command
    //
    // @return bool false if no tile needs to be force placed
    //
    int completeMap(Game& board, Position &current_position, Tile &current_tile);

    //--------------------------------------------------------------------------
    // fillEmptyTiles method
    // Fills map with empty tiles
    //
    // @param board the current board
    //
    void fillEmptyTiles(Game& board, Position current_position);

    //--------------------------------------------------------------------------
    // checkWin method
    // checks board if someone won
    //
    // @param board the current board
    //
    // @return int 1 if somebody won else 0
    //
    int winByLength(Game& board, Tile current_tile);

    //-------------------------------------------------------------------------- ------TODO
    // adaptTile method
    // Turns tile so colors connect
    //
    // @param field the game board of fields
    // @param tile the current tile
    // @param position the current position
    //
    // @return int 0 if everything worked 8 or 9 is somebody won
    //
    int winByLoop(std::map<Position*, Tile*> field,
            Tile &current_tile, Position current_position);

    //-------------------------------------------------------------------------- ------TODO
    // adaptTile method
    // Turns tile so colors connect
    //
    // @param field the game board of fields
    // @param tile the current tile
    // @param position the current position
    //
    // @return int 0 if everything worked 8 or 9 is somebody won
    //
    int whoWon(int win_code);
    void win(Game& board,std::vector<int> win_code);

    void gravicMode(Game& board);
};

#endif //ADDTILE_H_INCLUDED

