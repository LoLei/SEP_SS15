//------------------------------------------------------------------------------
// Write.cpp
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
//------------------------------------------------------------------------------
//

#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include "Position.h"
#include "Game.h"
#include "Tile.h"
#include "Command.h"
#include "Write.h"

//------------------------------------------------------------------------------
Write::Write() : Command("write")
{
}

//------------------------------------------------------------------------------
Write::~Write()
{
}

//------------------------------------------------------------------------------
int Write::execute(Game& board, std::vector<std::string>& user_input)
{
  if (board.getNumberOfTiles() == 0)
  {
    std::cout << "Board is empty!" << std::endl;
    return EMPTY_ERROR;
  }
  // case: filename without whitespace!
  if(user_input.size() != 2)
  {
    std::cout << "Error: Wrong parameter count!" << std::endl;
    return PARAMETER_COUNT_ERROR;
  }

  std::string file_name = user_input[1];
  struct FileHeader
  {
    char *signature;        // char[5] // TRAX
    char active_player;     // char // white (1) or red (2)
    signed char minim_x;    // s8
    signed char minim_y;    // s8
    signed char maxim_x;    // s8
    signed char maxim_y;    // s8
  };

  //------------------------------------------------------------------------
  // BoardTiles Struct
  // Simple struct for easier reading of file variables
  // Actual tiles in binary file
  //
  struct BoardTiles
  {
    char side;      // empty (0), + (1), / (2), \ (3)
    char top_color; // no figure (0), white end (1), red end (2)
  };

  FileHeader file_header;
  //------------------------------------------------------------------------
  // Write values into header
  // Find max and min coordinates
  file_header.minim_x = board.min_x_;
  file_header.minim_y = board.min_y_;
  file_header.maxim_x = board.max_x_;
  file_header.maxim_y = board.max_y_;
  // Signature and active player;
  file_header.signature = "TRAX";
  file_header.active_player = board.getActivePlayer();

  // Open file for writing
  // file_name is either argv[2] or command after write, i.e. user_input
  std::ofstream file(file_name,
    std::ios::out | std::ios::trunc | std::ios::binary);
  // Check if file is open, prints error if not, stops writing
  if (!file.is_open())
  {
    std::cout << "Cannot write file " << file_name << std::endl;
    return WRITE_ERROR;
  }

  // Write header into file
  file << file_header.signature;
  file << file_header.active_player;
  file << file_header.minim_x;
  file << file_header.minim_y;
  file << file_header.maxim_x;
  file << file_header.maxim_y;

  //------------------------------------------------------------------------
  // Write each line of the board
  // from (minim_x,minim_y) to (maxim_x,maxim_y)
  // from left to right, top to bottom
  // Write tiles into file
  BoardTiles board_tiles;

  // Write
  for (signed int y = board.min_y_; y <= board.max_y_; y++)
  {
    for (signed int x = board.min_x_; x <= board.max_x_; x++)
    {
      Position pos1(x, y);
      for (auto& x : board.field)
      {
        if (*x.first == pos1)
        {
          // Write type and color
          board_tiles.side = x.second->getType();
          board_tiles.top_color = x.second->getColor();

          file << board_tiles.side;
          file << board_tiles.top_color;
        }
      }
    }
  }
  file.close();
  return WRITE_SUCCESS;
}