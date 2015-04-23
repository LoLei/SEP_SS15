//------------------------------------------------------------------------------
// Game.cpp
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors:
// Markus Pichler 1331070
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
  tile_counter_ = 0;
  max_x_ = 0;
  max_y_ = 0;
  min_x_ = 0;
  min_y_ = 0;
  Tile::id_counter_ = 0;
}

//------------------------------------------------------------------------------
Game::~Game()
{
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
void Game::setMaximas(Position reference)
{
  if(reference.getX() > max_x_)
  {
    max_x_ = reference.getX();
  }
  if(reference.getY() > max_y_)
  {
    max_y_ = reference.getY();
  }
  if(reference.getX() < min_x_)
  {
    min_x_ = reference.getX();
  }
  if(reference.getY() < min_y_)
  {
    min_y_ = reference.getY();
  }
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
int Game::getNumberOfTiles()
{
  return tile_counter_;
}

//------------------------------------------------------------------------------
void Game::riseNumberOfTiles()
{
  tile_counter_++;
}
//------------------------------------------------------------------------------
int Game::userInputToCommand(std::vector<string> &vector_input)
{
  std::string string_input;
  std::getline(std::cin, string_input);
  std::istringstream is(string_input);
  std::string word;

  while(is >> word)
  {
    vector_input.push_back(word);
  }
  // If user enters blank line, prompt again
  if(vector_input.size() == 0)
  {
    return 1;
  }

  // make lower case
  for(std::size_t it = 0; it != vector_input[0].size(); it++)
  {
    vector_input[0][it] = tolower(vector_input[0][it]);
  }
  return 0;
}

//------------------------------------------------------------------------------
void Game::printTiles(std::map<Position*, Tile*> field)
{
  /*
  cout << endl << "Alte nicht sortierte field:" << endl;
  for (auto& x: field)
  {
    cout << x.first->toString() << ": " << x.second->getColorOut() <<" "
         << x.second->getTypeOut() << endl;
  }
  cout << "___" << endl;

  std::map<Position*, Tile*, customKeyComparator> map_sorted;
  for (signed int y = min_y_; y <= max_y_; y++)
  {
    for (signed int x = min_x_; x <= max_x_; x++)
    {
      Position pos1(x, y);
      for (auto& x : field)
      {
        if (*x.first == pos1)
        {
          map_sorted.emplace(x.first, x.second);
        }
      }
    }
  }
  // For win conditions maybe
  cout << endl << "Neue sortierte field:" << endl;
  for (auto& x : map_sorted)
  {
    cout << x.first->toString() << ": " << x.second->getColorOut() << " "
      << x.second->getTypeOut() << endl;
  }
*/
  //----------------------------------------------------------------------------
  /*
  cout << "    |";
  for (signed int i = min_x_; i <= max_x_; i++)
    cout << std::setfill (' ') << std::setw (3) << i << std::setw (4) << "||";
  cout << endl;
  int spalten1 = max_x_ - min_x_ + 1;
  cout << "    |";
  while(spalten1--)
  {
    cout << std::setfill ('=') << std::setw (7) << "||";
  }
  cout << endl;
  for(signed int y = min_y_; y <= max_y_; y++)
  {
    cout << std::setfill (' ') << std::setw (2) << y << ": |";
    int spalten = max_x_ - min_x_ + 1;
    for(signed int x = min_x_; x <= max_x_; x++)
    {
      Position pos1(x,y);
      for (auto& x: field)
      {
        if(*x.first == pos1)
        {
          cout << " " << x.second->getColorOut() << " "
          << x.second->getTypeOut() << " ||";
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
  }*/

    //--------------------------------------------------------------------------
    cout << "(white|red)" << endl;
  cout << "    |";
  for (signed int i = min_x_; i <= max_x_; i++)
    cout << std::setfill (' ') << std::setw (5) << i << std::setw (7) << "||";
  cout << endl;
  int spalten1 = max_x_ - min_x_ + 1;
  cout << "    |";
  while(spalten1--)
  {
    cout << std::setfill ('=') << std::setw (12) << "||";
  }
  cout << endl;
  for(signed int y = min_y_; y <= max_y_; y++)
  {
    cout << std::setfill (' ') << std::setw (2) << y << ": |";
    int spalten = max_x_ - min_x_ + 1;
    for(signed int x = min_x_; x <= max_x_; x++)
    {
      Position pos1(x,y);
      for (auto& x: field)
      {
        if(*x.first == pos1)
        {
          cout << " " << x.second->getColorOut() << " "
            << x.second->getTypeOut();
          cout << "(" << x.second->white_id_ << "|" << x.second->red_id_
            << ")" << " ||";
          break;
        }
      }
    }
    cout << endl;
    cout << "    |";
    while(spalten--)
    {
      cout << std::setfill ('=') << std::setw (12) << "||";
    }
    cout << endl;
  }
}

//------------------------------------------------------------------------------
void Game::freeTiles(std::map<Position*, Tile*> field)
{
  for (auto& x: field)
  {
    delete x.first;
    delete x.second;
  }
}

//------------------------------------------------------------------------------
void Game::run(std::string file_name, int graphic_mode)
{
  setRunning(true);

  int return_value = 0;

  Write createNewFile;
  Quit turnOff;
  AddTile addNewTile;

  do
  {
    std::cout << "sep> ";
    // get user input into a vactor
    std::vector<string> user_input;
    // If user enters blank line, prompt again
    if(userInputToCommand(user_input))
    {
      continue;
    }

    // choose case of command
    if(user_input[0] == "quit")
    {
      turnOff.execute(*this, user_input);
      //setRunning(false);
    }

    // ------------------------------------------write
    else if(user_input[0] == "write")
    {
      // case: filename without whitespace!
      if(user_input.size() != 2)
      {
        cout << "Error: Wrong parameter count!" << endl;
        continue;
      }
      createNewFile.execute(*this, user_input);
    }

    // --------------------------------------------------------addtile
    else if(user_input[0] == "addtile")
    {
      return_value = addNewTile.execute(*this, user_input);
      if(!(return_value == 8 || return_value == 9))
      {
        while(addNewTile.completeMap(field, user_input))
        {
          return_value = addNewTile.execute(*this, user_input);
        }
      }
      if (!((tile_counter_ == 0) && (return_value == 1)))
      {
        togglePlayer();
        if (graphic_mode == 1)
        {
          user_input[1] = file_name;
          createNewFile.execute(*this, user_input);
        }
      }
      // if auto complete
      if(return_value == 3)
      {
        setRunning(false);
      }
      // if someone won
      if(return_value == 8 || return_value == 9)
      {
        setRunning(false);
      }

      // if nobody won and tiles are not available
      if(return_value == 4)
      {
        setRunning(false);
      }
    }
    // --------------------------------------------------------
    else
    {
      cout << "Error: Unknown command!" << endl;
      continue;
    }
  } while( running_ );

  printTiles(field);
  freeTiles(field);
}
