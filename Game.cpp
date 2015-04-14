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

using std::cout;
using std::endl;
using std::string;

//------------------------------------------------------------------------------
Game::Game()
{
  activeplayer_ = COLOR_WHITE;
  starttile_ = NULL;
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
  switch (activeplayer_)
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
Color Game::getActivePlayer()
{
  return activeplayer_;
}

string Game::userInputToCommand(string user_input)
{
  try
  {
    // get first word in line -> command
    string first_word = user_input.substr(user_input.find_first_not_of(" "),
                             user_input.size());
    string command = first_word.substr(0,first_word.find_first_of(" "));
    // make lower case
    for(std::size_t it = 0; it != command.size(); it++)
    {
      command[it] = tolower(command[it]);
    }
      return command;
  }
  catch(...)
  {
    cout << "Invalid parameters(command)" << endl;
    return "";
  }
}

//------------------------------------------------------------------------------
void Game::run()
{
  setRunning(true);

  std::map<Position*, Tile*> karte;

  int tile_counter = 0;

  do
  {
    std::cout << "sep> ";
    string user_input;
    std::getline(std::cin, user_input);

    string command = userInputToCommand(user_input);
    // choose case of command
    if(command == "quit")
    {
      setRunning(false);
    }
    else if(command == "write")
    {
      //TODO
      std::cout << "write" << std::endl;
    }
    else if(command == "addtile")
    {
      Addtile newTile;
      newTile.addNewTile(user_input,karte,tile_counter);
    }
    else
    {
      continue;
    }
  } while( running_ );


  //----------------------------------------------------------
  // alle einträge ausgeben
  for (auto& x: karte)
  {
    cout << x.first->toString() << ": " << x.second->getColorOut() <<" "
         << x.second->getTypeOut() << endl;
    delete x.first;
    delete x.second;
  }
}
