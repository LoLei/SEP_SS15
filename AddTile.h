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
#include <map>
#include <vector>

#include "Command.h"

class Game;
class Tile;
class Position;

//------------------------------------------------------------------------------
// AddTile Class
// Class to add tiles
//
class AddTile : public Command
{
  private:
    //--------------------------------------------------------------------------
    // static ID counter for individual Tile IDs
    //
    static int id_counter_;
    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    AddTile(const AddTile &original);

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    AddTile &operator=(const AddTile &original);


  public:
    //--------------------------------------------------------------------------
    // defined return values
    // For easier reading and changing
    //
    static const int ABORT_ADDTILE = 1;
    static const int INVALID_COORDINATES_ERROR = 1;
    static const int INVALID_INPUT_ERROR = 1;
    static const int MEMORY_ERROR = 1;
    static const int COMPLETE_ERROR = 2;
    static const int COMPLETE_DONE = 1;
    static const int ADDTILE_SUCCESS = 0;
    static const int WIN_WHITE = 1;
    static const int WIN_RED = 2;
    static const int WIN_NONE = 0;
    static const int WIN = 5;
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
    // @param params the input the user enters
    //
    // @return int 0 if everything worked
    //
    int execute(Game &board, std::vector<std::string> &params);

    //--------------------------------------------------------------------------
    // setPositionAndTiletypeError method
    // Checks if command is correct and set position and tile type
    //
    // @param user_input the input the user enters
    // @param tile the current tile
    // @param position the current position
    //
    // @return bool true if everything worked
    //
    bool setPositionAndTiletypeError(std::vector<std::string> user_input,
      Tile &tile, Position &position);

    //--------------------------------------------------------------------------
    // colorCheck method
    // Checks if move is correct
    //
    // @param color_bool checks if color of nearby tile matches with the current
    // @param twisted if tile is twisted
    // @param lonely_tile if tile is placed not adjacent to two other tiles
    // @param tile the current tile
    //
    // @return bool true if everything worked
    //
    bool colorCheck(bool color_bool, bool &twisted, bool &lonely_tile,
      Tile &current_tile);

    //--------------------------------------------------------------------------
    // adaptTile method
    // Turns tile so colors connect
    //
    // @param board the current board
    // @param current_tile the current tile
    // @param current_position the current position
    //
    // @return int 0 if everything worked
    // @return int ABORT_ADDTILE if tile cannot be placed
    // @return int INVALID_COORDINATES_ERROR if field not connected to tile
    //
    int adaptTile(Game &board, Tile &current_tile, Position current_position);

    //--------------------------------------------------------------------------
    // completeMap method
    // Fills map with forced tiles
    //
    // @param board the current board
    // @param current_tile the current tile
    // @param current_position the current position
    //
    // @return int ADDTILE_SUCCESS if everything worked
    //
    int completeMap(Game &board, Position &current_position,
      Tile &current_tile);

    //--------------------------------------------------------------------------
    // fillEmptyTiles method
    // Fills map with empty tiles
    //
    // @param board the current board
    // @param current_position the current position
    //
    void fillEmptyTiles(Game &board, Position current_position);

    //--------------------------------------------------------------------------
    // winByLength method
    // Checks if someone won by length
    //
    // @param board the current board
    // @param current_tile the current tile
    //
    // @return int WIN_WHITE if white won
    // @return int WIN_RED if red won
    // @return int WIN_NONE if nobody won
    //
    int winByLength(Game &board, Tile current_tile);

    //--------------------------------------------------------------------------
    // winByLoop method
    // Checks if someone won by loop
    //
    // @param field the game board of fields
    // @param current_tile the current tile
    // @param current_position the current position
    //
    // @return int colors color of winning tile
    // @return int WIN_NONE if nobody won
    //
    int winByLoop(std::map<Position*, Tile*> field,
      Tile &current_tile, Position current_position);

    //--------------------------------------------------------------------------
    // whoWon method
    // Prints the winner
    //
    // @param win_code the play who won
    //
    // @return void
    //
    void whoWon(int win_code);

    //--------------------------------------------------------------------------
    // win method
    // Checks for winner, also checks if both won with one move, can end game
    //
    // @param board the current game
    // @param win_code the play who won
    //
    // @return void
    //
    void win(Game &board, std::vector<int> win_code);

    //--------------------------------------------------------------------------
    // addTheTile method
    // Adds tiles into the game field
    //
    // @param board the current game
    // @param current_position the current position
    // @param current_tile the current tile
    //
    // @return int 0 for OK and 1 for memory error
    //
    int addTheTile(Game &board, Position current_position, Tile current_tile);

    //--------------------------------------------------------------------------
    // graphicMode method
    // Checks whether graphic mode is enabled, if yes will write into file
    //
    // @param board the current game
    //
    // @return void
    //
    void graphicMode(Game &board);

};

#endif //ADDTILE_H_INCLUDED

