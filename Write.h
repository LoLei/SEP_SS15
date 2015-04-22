//------------------------------------------------------------------------------
// Write.h
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors: 
// Lorenz Leitner 1430211
//------------------------------------------------------------------------------
//

#ifndef WRITE_H_INCLUDED
#define WRITE_H_INCLUDED

#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include "Position.h"
#include "Game.h"
#include "Tile.h"
#include "Command.h"
#include "WriteException.h"

//------------------------------------------------------------------------------
// Write Class
// Class for writing binary files containing the game board
//
class Write :public Command
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    Write(const Write& original);

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    Write& operator=(const Write& original);

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    Write();

    //--------------------------------------------------------------------------
    // Destructor
    //
    //~Write();

    //--------------------------------------------------------------------------
    // execute method
    // Executes command write, creates file
    // 
    // @param board the game board
    // @param user_input the input the user enters, will be file name
    //
    // @return int 0 if everything worked
    //
    int execute(Game& board, std::vector<std::string>& user_input);
};

#endif //WRITE_H_INCLUDED

