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

#include <iomanip>
#include <sstream>
#include <cctype>

//#include "Tile.h"
#include "AddTile.h"
//#include "Position.h"
#include "Write.h"
#include "Command.h"
#include "Quit.h"
#include "Play.h"
#include "UnknownCommandException.h"
#include "UsageException.h"
#include "EmptyBoardException.h"
#include "WrongParameterException.h"
#include "Karte.h"

#include "Game.h"

using std::string;

//------------------------------------------------------------------------------
Game::Game() : activeplayer_(COLOR_WHITE), starttile_(NULL), tile_counter_(0),
               max_x_(0), max_y_(0), min_x_(0), min_y_(0), moveID(0)
{
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
string Game::getOutputFilename()
{
  return output_filename_;
}

//------------------------------------------------------------------------------
void Game::setOutputFilename(string filename)
{
  output_filename_ = filename;
}

//------------------------------------------------------------------------------
void Game::riseNumberOfTiles()
{
  tile_counter_++;
}
//------------------------------------------------------------------------------
int Game::userInputToCommand(std::vector<string> &vector_input)
{
  string string_input;
  std::getline(std::cin, string_input);
  std::istringstream is(string_input);
  string word;

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
void Game::freeTiles(std::map<Position*, Tile*> field)
{
  for (auto& x: field)
  {
    delete x.first;
    delete x.second;
  }
}

//------------------------------------------------------------------------------
void Game::run()
{
  setRunning(true);

  std::vector<Command*> command_;
  command_.push_back(new Write());
  command_.push_back(new Quit());
  command_.push_back(new AddTile());
//  command_.push_back(new Play());

  do
  {
//    std::cout << "sep> ";


    if(getActivePlayer() == COLOR_WHITE)
    {
      std::cout << "w:" << getNumberOfTiles() << " > ";
    }
    if(getActivePlayer() == COLOR_RED)
    {
      std::cout << "r:" << getNumberOfTiles() << " > ";
    }


    // get user input into a vector
    std::vector<string> user_input;
    // If user enters blank line, prompt again
    if(userInputToCommand(user_input))
    {
      continue;
    }

    else if(user_input[0] == "print")// --------------------------------------------------------test zwecke
      printTiles();

    moveID = getNumberOfTiles();
    int ansonsten = 1;

    for (auto& current_command : command_)
    {
      if(current_command->getName() == user_input[0])
      {
        current_command->execute(*this, user_input);

        ansonsten = 0;
        break;
      }
    }
    if(ansonsten)
    {
      std::cout << "Error: Unknown command!" << std::endl;
      continue;
    }
  } while(running_);

  printTiles();

  freeTiles(field);
}

//--------------------------------------------------------------------------------tests
void Game::printTiles()
{
  int spalten1;
  std::cout << "color|type|move|white|red|" << std::endl;
  std::cout << "    |";
  for (signed int i = min_x_; i <= max_x_; i++)
    std::cout << std::setfill (' ') << std::setw (6) << i << std::setw (7) << "||";
  std::cout << std::endl;
  spalten1 = max_x_ - min_x_ + 1;
  std::cout << "    |";
  while(spalten1--)
  {
    std::cout << std::setfill ('=') << std::setw (13) << "||";
  }
  std::cout << std::endl;
  for(signed int y = min_y_; y <= max_y_; y++)
  {
    std::cout << std::setfill (' ') << std::setw (2) << y << ": |";
    int spalten = max_x_ - min_x_ + 1;
    for(signed int x = min_x_; x <= max_x_; x++)
    {
      Position pos1(x,y);
      for (auto& x: field)
      {
        if(*x.first == pos1)
        {
          std::cout << " " << x.second->getColorOut() << "|" << x.second->getTypeOut()
              << "|" << x.second->getMove();
          std::cout << "|" << x.second->getId(COLOR_WHITE) << "|" << x.second->getId(COLOR_RED)
             << " ||";
          break;
        }
      }
    }
    std::cout << std::endl;
    std::cout << "    |";
    while(spalten--)
    {
      std::cout << std::setfill ('=') << std::setw (13) << "||";
    }
    std::cout << std::endl;
  }
}