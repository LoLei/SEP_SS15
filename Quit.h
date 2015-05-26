//------------------------------------------------------------------------------
// Quit.h
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
//------------------------------------------------------------------------------
//

#ifndef QUIT_H_INCLUDED
#define QUIT_H_INCLUDED

#include <string>
#include <vector>

#include "Command.h"
#include "Game.h"

class Quit : public Command
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    Quit(const Quit &original);

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    Quit &operator=(const Quit &original);

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    Quit();

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Quit();

    //--------------------------------------------------------------------------
    // execute method
    // Executes command
    //
    // @param board the game board
    // @param user_input the input the user enters
    //
    // @return int 0 if everything worked
    //
    int execute(Game &board, std::vector<std::string> &params);

    static const int QUIT_SUCCESS = 0;
    static const int QUIT_ERROR = 1;
};

#endif //QUIT_H_INCLUDED

