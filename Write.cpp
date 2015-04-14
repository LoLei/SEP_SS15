//------------------------------------------------------------------------------
// Filename: Write.cpp
// Description: Used for writing binary file
// Authors: Lorenz Leitner
// Tutor: Philipp Loibl
// Group: 11574
// Created: 14.04.2015
// Last change: 14.04.2015
//------------------------------------------------------------------------------

#include "Write.h"

#define AP_OFFSET     4
#define AP_WHITE      1
#define AP_RED        2
#define NO_FIGURE     0
#define SIDE_CROSS    1
#define SIDE_CURVE_1  2
#define SIDE_CURVE_2  3
#define TOP_WHITE     1
#define TOP_RED       2

Write::Write() : Command("Write")
{
}

//------------------------------------------------------------------------------
void Write::createNewFile(std::string user_input, std::map<Position*, Tile*> &karte,
  int &tile_counter)
{
  std::string file_name = user_input.substr(6);
  long pos;

  typedef struct
  {
    char *signature;    // char[4] // TRAX
    char active_player; // char // white (1) or red (2)
    signed char minX;   // s8
    signed char minY;   // s8
    signed char maxX;   // s8
    signed char maxY;   // s8
  } FileHeader;         

  typedef struct
  {
    char side;      // no figure (0), cross (1), Kurve1 "/" (2), Kurve2 "\" (3)
    char top_color; // no figure (0), white end (1), red end (2) // offset 1
  } BoardTiles;

  // Write values into header
  FileHeader file_header;
  file_header.signature = "TRAX";
  file_header.active_player = AP_WHITE;
  file_header.minX = 0;
  file_header.minY = 0;
  file_header.maxX = 1;
  file_header.maxY = 1;

  try
  {
    // Open file for writing
    // file_name is either argv[2] or command after write, i.e. user_input
    std::ofstream file("file_name",
      std::ios::out | std::ios::trunc | std::ios::binary);
    // Check if file is open, prints error if not, stops writing
    if (!file.is_open())
    {
      throw WriteException();
    }

    // Write header into file
    file << file_header.signature;
    file << file_header.active_player;
    file << file_header.minX;
    file << file_header.minY;
    file << file_header.maxX;
    file << file_header.maxY;

    // Write each line of the board from (minX,minY) to (maxX,maxY)
    // from left to right
    // Write tiles into file
    BoardTiles board_tiles;
    //--------------------------------------------------------------------------//
    // Active player = White, set already
    board_tiles.side = SIDE_CROSS;
    board_tiles.top_color = TOP_RED;

    file << board_tiles.side;
    file << board_tiles.top_color;
    // Save position
    pos = file.tellp();
    //--------------------------------------------------------------------------//
    // Active player = Red
    file_header.active_player = AP_RED;
    // Sets position to offset 4 for active player in binary file
    file.seekp(AP_OFFSET);
    file << file_header.active_player;
    // Sets position to where it left off
    file.seekp(pos);

    board_tiles.side = SIDE_CROSS;
    board_tiles.top_color = TOP_RED;

    file << board_tiles.side;
    file << board_tiles.top_color;
    // Save position
    pos = file.tellp();
    //--------------------------------------------------------------------------//
    // Active player = White
    file_header.active_player = AP_WHITE;
    // Sets position to offset 4 for active player in binary file
    file.seekp(AP_OFFSET);
    file << file_header.active_player;
    // Sets position to where it left off
    file.seekp(pos);

    board_tiles.side = SIDE_CROSS;
    board_tiles.top_color = TOP_RED;

    file << board_tiles.side;
    file << board_tiles.top_color;
    // Save position
    pos = file.tellp();
    //--------------------------------------------------------------------------//
    // Active player = Red
    file_header.active_player = AP_RED;
    // Sets position to offset 4 for active player in binary file
    file.seekp(AP_OFFSET);
    file << file_header.active_player;
    // Sets position to where it left off
    file.seekp(pos);

    board_tiles.side = SIDE_CURVE_2;
    board_tiles.top_color = TOP_RED;

    file << board_tiles.side;
    file << board_tiles.top_color;
    // Save position
    pos = file.tellp();
    //--------------------------------------------------------------------------//
    // Close file
    file.close();
  }
  catch (WriteException& e1)
  {
    std::cout << e1.what() << "file_name" << std::endl;
  }
  catch (std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }
}