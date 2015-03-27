#include "Game.h"
#include <iostream>
#include <string>

// Default constructor
Game::Game()
{
  active_player_ = COLOR_WHITE;
  start_tile_ = nullptr;
}

// Destructor
Game::~Game()
{

}

void Game::setStartTile(Tile x)
{
  //*start_tile_ = x;
  start_tile_ = &x;
}

void Game::run()
{
  running_ = true;
  std::string check;
  while (running_ == true)
  {
    std::cout << "sep> ";
    std::cin >> check;
    if (check == "quit")
    {
      running_ = false;
      break;
    }
  }
}

void Game::setRun(bool x)
{
  running_ = x;
}

void Game::togglePlayer()
{
  if (active_player_ == COLOR_RED)
  {
    active_player_ = COLOR_WHITE;
  }
  else if (active_player_ == COLOR_WHITE)
  {
    active_player_ = COLOR_RED;
  }
}

Color Game::getActivePlayer()
{
  return active_player_;
}