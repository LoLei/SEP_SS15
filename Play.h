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

#ifndef PLAY_H_INCLUDED
#define PLAY_H_INCLUDED

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
class Play:public Command
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    Play(const Play& original);

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    Play& operator=(const Play& original);


  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    Play();

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Play();

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
    int randomMove(Game& board, std::vector<std::string>& params);
    int randomIDMove(Game& board, std::vector<std::string>& params);
    std::string randomType();
    std::string randomType(std::string not_type);
    int lookForOpenEnds(Game& board, std::vector<std::string>& params);
};

#endif //PLAY_H_INCLUDED

