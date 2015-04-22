//------------------------------------------------------------------------------
// Game.h
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors: Markus Pichler 1331070
//
//------------------------------------------------------------------------------
//

#ifndef GAME_H
#define GAME_H

#include "Tile.h"
#include "AddTile.h"
#include "Position.h"
#include "Write.h"
#include "Command.h"
#include "Quit.h"
#include <iostream>
#include <string>
#include <cctype>
#include <map>
#include <iomanip>
#include <sstream>

//------------------------------------------------------------------------------
// Game Class
//
class Game
{
  private:

    //--------------------------------------------------------------------------
    // Color of the active Player
    //
    Color activeplayer_;

    //--------------------------------------------------------------------------
    // Pointer of the Starttile
    //
    Tile* starttile_;

    //--------------------------------------------------------------------------
    // Bool is the game is running
    //
    bool running_;

    //--------------------------------------------------------------------------
    // counts the tiles
    //
    int tile_counter_;

    int userInputToCommand(std::vector<std::string> &user_input);

  public:

    signed int max_x_;
    signed int max_y_;
    signed int min_x_;
    signed int min_y_;

    void setMaximas(Position reference);

    //--------------------------------------------------------------------------
    // Constructor
    //
    Game();

    std::map<Position*, Tile*> field;

    //Game(Type side, Color orientation);

    //--------------------------------------------------------------------------
    // Copy Constructor
    // Makes a copy of another Game Object.
    // @param original Original to copy.
    //
    // Game(const Game &);

    //--------------------------------------------------------------------------
    // Run Methode
    // ...
    // @param
    //
    void run(std::string file_name, int graphic_mode);

    //--------------------------------------------------------------------------
    // toggle Player Methode
    // ...
    // @param
    //
    void togglePlayer();
    void riseNumberOfTiles();
    //--------------------------------------------------------------------------
    // Setter Methods
    //
    void setStartTile(Tile* starttile);

    void setRunning(bool running);

    //--------------------------------------------------------------------------
    // Getter Methods
    //
    Color getActivePlayer();
    int getNumberOfTiles();

    //--------------------------------------------------------------------------
    // Destructor
    //
    //~Game();

    void printTiles(std::map<Position*, Tile*> karte);
    void freeTiles(std::map<Position*, Tile*> karte);
};
#endif // GAME_H