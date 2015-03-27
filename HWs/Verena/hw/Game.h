//------------------------------------------------------------------------------
// Game.h
//
// Group: 9, study assistant: Philipp Loibl
//
// Authors: Verena Niederwanger (1430778)
//------------------------------------------------------------------------------
//
#ifndef GAME_H
#define GAME_H
#include "Color.h"
#include "Tile.h"

class Game
{
public:
	Color activeplayer;
	Tile *starttile;
	bool running;

	Game();
	Game(const Game &copy);
	~Game();

	void setStartTile (Tile x) { starttile = &x; }
	void setRunning (bool value) { running = value; }

	void run();
	void togglePlayer();

	Color getActivePlayer() const { return activeplayer; }

};

#endif

