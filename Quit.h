//------------------------------------------------------------------------------
// Quit.h
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors: 
// Markus Pichler 1331070
//------------------------------------------------------------------------------
//

#ifndef QUIT_H_INCLUDED
#define QUIT_H_INCLUDED

#include <string>
#include <vector>
#include "Position.h"
#include "Command.h"
#include "Game.h"


class Quit:public Command
{
  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    Quit();

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

  //private:
    //--------------------------------------------------------------------------
    // Destructor
    //
    //~Quit();
};

#endif //QUIT_H_INCLUDED

