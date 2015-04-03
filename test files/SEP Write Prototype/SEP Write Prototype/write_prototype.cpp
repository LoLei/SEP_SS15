// Version 2.2
// TODO Swapping active player only happens when next player makes a turn
// not when a forced tile is placed
// TODO Proper try except
// TODO Error when board is empty

#include <iostream>
#include <fstream>
#include <string>

#define TYPE 1480675924 // TRAX in dec from hex in little endian
#define AP_OFFSET     4
#define AP_WHITE      1
#define AP_RED        2
#define NO_FIGURE     0
#define SIDE_CROSS    1
#define SIDE_CURVE_1  2
#define SIDE_CURVE_2  3
#define TOP_WHITE     1
#define TOP_RED       2

void writeFile(std::string file_name);

//------------------------------------------------------------------------------
// Main function - used to call write function and pass arguments
//
// @param argc the amount of arguments passed to the programm
// @param argv list of arguments
//        first one can be -g, makes write be called at each AddTile
//        second one is file name for the output binary file
//
// @return int for success
//
int main(int argc, char *argv[])
{
  std::string file_name;
  // File name is either from initial program start or from sep> command
  if (argc == 3)
  {
    file_name = argv[2];
    //std::cout << file_name << std::endl;
  }
  writeFile(file_name);
  return 0;
}

//------------------------------------------------------------------------------
// Write function - used to write the actual binary file
//
// @param file_name the name the user wants the output file to be called
//
void writeFile(std::string file_name)
{
  long pos;

  typedef struct
  {
    char *signature; // char[4] // TRAX
    char active_player; // char // white (1) or red (2)
    signed char minX; // signed char
    signed char minY; // signed char
    signed char maxX; // signed char
    signed char maxY; // signed char
  } FileHeader; // signed char

  typedef struct
  {
    char side; // no figure (0), cross (1), Kurve1 "/" (2), Kurve2 "\" (3)
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
    std::ofstream file(file_name,
      std::ios::out | std::ios::trunc | std::ios::binary);
    // Check if file is open, prints error if not, stops writing
    if (!file.is_open())
    {
      throw - 1;
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
  catch (int x)
  {
    std::cout << "Cannot write file " << file_name << std::endl;
  }
}
