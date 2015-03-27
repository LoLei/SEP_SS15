// TODO: Add private copy constructor

#ifndef GAME_H
#define GAME_H

#include "Tile.h"

class Game
{
private:
  Color active_player_;
  Tile *start_tile_;
  bool running_;
public:
  // Default constructor
  Game();
  ~Game(); // Destructor

  // Methods
  void setStartTile(Tile x);
  void run();
  void setRun(bool x);
  void togglePlayer();
  Color getActivePlayer();
};

#endif