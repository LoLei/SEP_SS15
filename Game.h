//------------------------------------------------------------------------------
// Game.h
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
//------------------------------------------------------------------------------
//

#ifndef GAME_H
#define GAME_H

#include "Color.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>

class Tile;
class Position;

//------------------------------------------------------------------------------
// Game Class
// Class concerning the active game
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
    Tile *starttile_;

    //--------------------------------------------------------------------------
    // Bool is the game is running
    //
    bool running_;

    //--------------------------------------------------------------------------
    // counts the tiles
    //
    int tile_counter_ = 0;

    //--------------------------------------------------------------------------
    // individual identification for move
    //
    int moveID = 0;
    //--------------------------------------------------------------------------
    // userInputToCommand method
    // parses the user input as commands
    //
    // @param user_input input entered from the user
    //
    int userInputToCommand(std::vector<std::string> &user_input);

    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    Game(const Game &original);

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    Game &operator=(const Game &original);

    std::string output_filename_;

  public:

    signed int max_x_ = 0;
    signed int max_y_ = 0;
    signed int min_x_ = 0;
    signed int min_y_ = 0;

    //--------------------------------------------------------------------------
    // map
    // Store tiles with positions
    //
    std::map<Position*, Tile*> field;

    //--------------------------------------------------------------------------
    // Constructor
    //
    Game();

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Game();


    //--------------------------------------------------------------------------
    // Setter Methods
    //
    void setStartTile(Tile *starttile);
    void setRunning(bool running);
    void setOutputFilename(std::string);

    //--------------------------------------------------------------------------
    // Getter Methods
    //
    Color getActivePlayer();
    int getNumberOfTiles();
    int getMoveId();
    std::string getOutputFilename();

    //--------------------------------------------------------------------------
    // setMaximas method
    // sets the maximum coordinates
    // @param reference position which is used as a reference to set coordinates
    //
    void setMaximas(Position reference);

    //--------------------------------------------------------------------------
    // run method
    // Starts the game
    // @param file_name file name to write file
    // @param graphic_mode used to test if grapic mode is enabled
    //
    void run();

    //--------------------------------------------------------------------------
    // toggle Player method
    // Switches the active player
    //
    void togglePlayer();

    //--------------------------------------------------------------------------
    // riseNumberOfTiles method
    // Increases the tile counter
    //
    void riseNumberOfTiles();

    //--------------------------------------------------------------------------
    // riseMoveId method
    // Increases the move ID
    //
    void riseMoveId();

    //--------------------------------------------------------------------------
    // freeTiles method
    // deletes tiles
    //
    // @param field map of tiles
    //
    void freeTiles(std::map<Position*, Tile*> field);
};
#endif // GAME_H