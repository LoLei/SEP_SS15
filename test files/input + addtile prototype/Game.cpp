//------------------------------------------------------------------------------
// Game.cpp
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors: Markus Pichler 1331070
// 
//------------------------------------------------------------------------------
//

#include "Game.h"
//#include "Tile.h"
#include "AddTile.h"
#include <iostream>
#include <string>
#include <cctype>

using std::string;

//------------------------------------------------------------------------------
Game::Game()
{
  activeplayer_ = COLOR_WHITE;
  starttile_ = NULL;
}

//------------------------------------------------------------------------------
Color Game::getActivePlayer()
{
  return activeplayer_;
}

//------------------------------------------------------------------------------
void Game::setStartTile(Tile* starttile)
{
  starttile_ = starttile;
}

//------------------------------------------------------------------------------
void Game::setRunning(bool running)
{
  running_ = running;
}

//------------------------------------------------------------------------------
void Game::togglePlayer()
{
  switch (getActivePlayer())
  {
    case COLOR_WHITE:
      activeplayer_ = COLOR_RED;
      break;
    case COLOR_RED:
      activeplayer_ = COLOR_WHITE;
      break;
  }
}

//------------------------------------------------------------------------------
void Game::run()
{
  setRunning(true);
  string user_input;
  Addtile addtile;
  Tile current_tile;
  Position current_position(0,0);
  
  do
  {
    std::cout << "sep> ";
    std::getline(std::cin, user_input);
    // get first word in line -> command
    string str1 = user_input.substr(user_input.find_first_not_of(" "),user_input.size());
    string str2 = str1.substr(0,str1.find_first_of(" "));
    // make lower case
    for(std::size_t it = 0; it != str2.size(); it++)
    {
      str2[it] = tolower(str2[it]);
    }
    // choose case of command
    if(str2 == "quit")
    {
      setRunning(false);
    }
    else if(str2 == "write")
    {
      //TODO
      std::cout << "write" << std::endl;
    }
    else if(str2 == "addtile")
    {
      //TODO
      if(addtile.valuecommand(user_input, current_tile, current_position, getActivePlayer()))
      {
        std::cout << "funct" << std::endl;
        //std::cout << "work2" << std::endl;
      }
    }
  } while( running_ );
}
