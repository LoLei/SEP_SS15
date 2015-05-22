//------------------------------------------------------------------------------
// Write.h
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
//------------------------------------------------------------------------------
//

#ifndef WRITE_H_INCLUDED
#define WRITE_H_INCLUDED

#include <string>
#include <iostream>
#include "Command.h"

class Game;

//------------------------------------------------------------------------------
// Write Class
// Class for writing binary files containing the game board
//
class Write : public Command
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
    virtual ~Write();

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

    static const int WRITE_ERROR = 0;
    static const int EMPTY_ERROR = 1;
    static const int PARAMETER_COUNT_ERROR = 1;
    static const int WRITE_SUCCESS = 0;
};

#endif //WRITE_H_INCLUDED

