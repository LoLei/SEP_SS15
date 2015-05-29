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
    // Pointer of the start tile
    //
    Tile *starttile_;

    //--------------------------------------------------------------------------
    // Bool is the game is running
    //
    bool running_;

    //--------------------------------------------------------------------------
    // counts the tiles
    //
    int tile_counter_;

    //--------------------------------------------------------------------------
    // the maximas and minimas of the game field
    //
    signed int max_x_;
    signed int max_y_;
    signed int min_x_;
    signed int min_y_;

    //--------------------------------------------------------------------------
    // individual identification for move
    //
    int moveID;

    //--------------------------------------------------------------------------
    // name of the output file
    //
    std::string output_filename_;

    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    Game(const Game &original);

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    Game &operator=(const Game &original);


  public:
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
    // userInputToCommand method
    // parses the user input as commands
    //
    // @param user_input input entered from the user
    //
    int userInputToCommand(std::vector<std::string> &user_input);

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
    // @param graphic_mode used to test if graphic mode is enabled
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

    //--------------------------------------------------------------------------
    // getExtrema method
    // get max/min x/y
    //
    // @param extrema '+' for maximum and '-' for minimum
    // @param axis 'x' for x and 'y' for y
    //
    signed int getExtrema(char extrema, char axis);
    void setExtrema(char extrema, char axis, int number);

};
#endif // GAME_H