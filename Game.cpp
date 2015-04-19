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
#include "Karte.h"

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
    default:
      break;
  }
}

//------------------------------------------------------------------------------
Color Game::getActivePlayer()
{
  return activeplayer_;
}

//------------------------------------------------------------------------------
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
void Game::printTiles(std::map<Position*, Tile*> karte)
{
  cout << endl << "Alte nicht sortierte Karte:" << endl;
  for (auto& x: karte)
  {
    cout << x.first->toString() << ": " << x.second->getColorOut() <<" "
         << x.second->getTypeOut() << endl;
  }
  cout << "___" << endl;

  std::map<Position*, Tile*, customKeyComparator> karte2;
  for (auto& x : karte)
  {
    karte2.emplace(x.first, x.second);
  }
  cout << endl << "Neue sortierte Karte:" << endl;
  for (auto& x : karte2)
  {
    cout << x.first->toString() << ": " << x.second->getColorOut() << " "
      << x.second->getTypeOut() << endl;
  }

  //----------------------------------------------------------------------------
/*
  for(signed int y = Addtile::min_y_; y <= Addtile::max_y_; y++)
  {
    for(signed int x = Addtile::min_x_; x <= Addtile::max_x_; x++)
    {
      Position pos1(x,y);
      for (auto& x: karte)
      {
        if(*x.first == pos1)
        {
          cout << x.first->toString() << ": " << x.second->getColorOut() <<" "
          << x.second->getTypeOut() << endl;
          break;
        }
      }
    }
  }
  */
  // ----
  cout << "    |";
  for (signed int i = Addtile::min_x_; i <= Addtile::max_x_; i++)
    cout << std::setfill (' ') << std::setw (3) << i << std::setw (4) << "||";
  cout << endl;
  int spalten1 = Addtile::max_x_ - Addtile::min_x_ + 1;
  cout << "    |";
  while(spalten1--)
  {
    cout << std::setfill ('=') << std::setw (7) << "||";
  }
  cout << endl;
  for(signed int y = Addtile::min_y_; y <= Addtile::max_y_; y++)
  {
    cout << std::setfill (' ') << std::setw (2) << y << ": |";
    int spalten = Addtile::max_x_ - Addtile::min_x_ + 1;
    for(signed int x = Addtile::min_x_; x <= Addtile::max_x_; x++)
    {
      Position pos1(x,y);
      for (auto& x: karte)
      {
        if(*x.first == pos1)
        {
          //cout << " " << x.first->toString();
          cout << " " << x.second->getColorOut() << " " << x.second->getTypeOut() << " ||";
          break;
        }
      }
    }
    cout << endl;
    cout << "    |";
    while(spalten--)
    {
      cout << std::setfill ('=') << std::setw (7) << "||";
    }
    cout << endl;
  }

  cout << endl << "active player:" << endl;
  for(signed int y = Addtile::min_y_; y <= Addtile::max_y_; y++)
  {
    for(signed int x = Addtile::min_x_; x <= Addtile::max_x_; x++)
    {
      Position pos1(x,y);
      for (auto& x: karte)
      {
        if(*x.first == pos1)
        {
          cout << x.first->toString() << ": " << x.second->getPlayerColorOut() << endl;
          break;
        }
      }
    }
  }
  //---

}

//------------------------------------------------------------------------------
void Game::freeTiles(std::map<Position*, Tile*> karte)
{
  for (auto& x: karte)
  {
    delete x.first;
    delete x.second;
  }
}

//------------------------------------------------------------------------------
void Game::run(std::string file_name, int graphic_mode)
{
  setRunning(true);

  std::map<Position*, Tile*> karte;

  int tile_counter = 0;

  do
  {
    std::cout << "sep> ";
    string user_input;
    std::getline(std::cin, user_input);

    // If user enters blank line, prompt again
    if (user_input == "")
    {
      continue;
    }

    string command = userInputToCommand(user_input);
    // choose case of command
    if(command == "quit")
    {
      setRunning(false);
    }
    else if(command == "write")
    {
      Write createNewFile;
      createNewFile.createNewFile(user_input,karte,tile_counter,getActivePlayer());
    }
    else if(command == "addtile")
    {
      Addtile newTile;
      newTile.addNewTile(user_input,karte,tile_counter,getActivePlayer());
      string forAddtile;
      while(newTile.completeMap(karte, tile_counter, forAddtile)) 
      {
        newTile.addNewTile(forAddtile,karte,tile_counter,getActivePlayer());
      }
      togglePlayer();
    }
    if (graphic_mode == 1)
    {
      user_input = "write " + file_name;
      Write createNewFile;
      createNewFile.createNewFile(user_input, karte, tile_counter,getActivePlayer());
    }
    else
    {
      continue;
    }
  } while( running_ );

  printTiles(karte);
  freeTiles(karte);
}
