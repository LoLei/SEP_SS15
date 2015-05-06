//------------------------------------------------------------------------------
// Game.cpp
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
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
  tile_counter_ = 0;
  max_x_ = 0;
  max_y_ = 0;
  min_x_ = 0;
  min_y_ = 0;
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
    std::cin.clear();
    return 1;
  }

  if(vector_input[0][0] == EOF)
  {
    std::cin.clear();
    std::cin.ignore(INT_MAX);
    std::cout << std::endl;
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
void Game::printTiles(std::map<Position*, Tile*> field, int i)
{
  int spalten1;
  std::map<Position*, Tile*, customKeyComparator> field1;

  switch(i)
  {
    case 1:
      for (auto& x : field)
      {
          field1.emplace(x.first, x.second);
      }

      // For win conditions maybe
      cout << endl << "Neue sortierte field:" << endl;
      for (auto& x : field1)
      {
        cout << x.first->toString() << ": " << x.second->getColorOut() << " "
          << x.second->getTypeOut() << endl;
      }

      break;
//----------------------------------------------------------------------------
    case 2:
      cout << "    |";
      for (signed int i = min_x_; i <= max_x_; i++)
        cout << std::setfill (' ') << std::setw (3) << i << std::setw (4) << "||";
      cout << endl;
      spalten1 = max_x_ - min_x_ + 1;
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
      }
      break;
//--------------------------------------------------------------------------
    case 3:
      cout << "(white|red)" << endl;
      cout << "    |";
      for (signed int i = min_x_; i <= max_x_; i++)
        cout << std::setfill (' ') << std::setw (5) << i << std::setw (7) << "||";
      cout << endl;
      spalten1 = max_x_ - min_x_ + 1;
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
              cout << "(" << x.second->getId(COLOR_WHITE) << "|" << x.second->getId(COLOR_RED)
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
      break;
    default:
      break;
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
  Play automatic;

  do
  {
    //std::cout << "sep> ";


                                              // test zwecke ----------------------TODO
    if(getActivePlayer() == COLOR_WHITE)
    {
      std::cout << "w:" << getNumberOfTiles() << " > ";
    }
    if(getActivePlayer() == COLOR_RED)
    {
      std::cout << "r:" << getNumberOfTiles() << " > ";
    }



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
    }

    // ------------------------------------------write
    else if(user_input[0] == "write")
    {
      createNewFile.execute(*this, user_input);
    }

    // --------------------------------------------------------addtile
    else if(user_input[0] == "addtile")
    {
      return_value = addNewTile.execute(*this, user_input);
      // 1 for fail, 2 for game end, 0 go on

      // no tile set or a fail happend
      if(graphic_mode && tile_counter_ && (return_value != 1))
      {
        user_input.pop_back();
        user_input[1] = file_name;
        createNewFile.execute(*this, user_input);
      }
    }

    // --------------------------------------------------------test zwecke
    else if(user_input[0] == "print1")
    {
      printTiles(field,1);
    }
    else if(user_input[0] == "print2")
    {
      printTiles(field,2);
    }
    else if(user_input[0] == "print3")
    {
      printTiles(field,3);
    }
    // --------------------------------------------------------test zwecke

    else if(user_input[0] == "play")
    {
      int exe = automatic.execute(*this, user_input);
      for(int i = 1; i < static_cast<int>(user_input.size()); i++)
      {
        std::cout << user_input[i] << " ";
      }
      std::cout << std::endl;
      if(exe)
        addNewTile.execute(*this, user_input);


      if(graphic_mode && tile_counter_ && (return_value != 1))
      {
        user_input.pop_back();
        user_input[1] = file_name;
        createNewFile.execute(*this, user_input);
      }
    }
    // --------------------------------------------------------
    else
    {
      cout << "Error: Unknown command!" << endl;
      continue;
    }
  } while(running_);

  //printTiles(field);
  freeTiles(field);
}
