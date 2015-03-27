//------------------------------------------------------------------------------
// game.cpp
//
// Group: 9, study assistant: Philipp Loibl
//
// Authors: Verena Niederwanger (1430778)
//------------------------------------------------------------------------------
//
#include "Game.h"
#include <iostream>
#include <string>
#include <sstream>

//constructor
Game::Game() : activeplayer(COLOR_WHITE), starttile(nullptr)
{
}

//copy constructor
Game::Game(const Game &copy)
{
}


//destructor
Game::~Game()
{
}

//run-Methode
void Game::run()
{
	running = true;
	std::string newline = "";
	while (running == true)
	{
		std::cout << "sep> " ;
		std::cin >> newline ;
		if (newline == "quit")
		{
			running = false;
		}
	}
}

//togglePlayer-Methode
void Game::togglePlayer()
{
	if (activeplayer == COLOR_WHITE)
		activeplayer = COLOR_RED;
	else
		activeplayer = COLOR_WHITE;
	
}


