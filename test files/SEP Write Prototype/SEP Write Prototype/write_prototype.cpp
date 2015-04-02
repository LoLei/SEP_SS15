// Version 2

#include <iostream>
#include <fstream>

#define TYPE 1480675924 // TRAX in dec from hex in little endian

int main()
{
  typedef struct
  {
    char *signature; // char[4] // TRAX // hex: 54 52 41 58 // little endian: 58 41 52 54 // Offset 0
    char active_player; // char // white (1) or red (2) // Offset 4
    signed char minX; // signed char
    signed char minY; // signed char
    signed char maxX; // signed char
    signed char maxY; // signed char
  } FileHeader; // signed char

  typedef struct
  {
    char side; // char // no figure (0), cross (1), Kurve1 "/" (2), Kurve2 "\" (3) // offset 0
    char top_color; // char // no figure (0), white end (1), red end (2) // offset 1
  } BoardTiles;

  // Write values into header
  FileHeader file_header;
  //file_header.signature = { 'T', 'R', 'A', 'X', '\0' };
  file_header.signature = "TRAX";
  file_header.active_player = 1;
  file_header.minX = 0;
  file_header.minY = 0;
  file_header.maxX = 1;
  file_header.maxY = 1;

  // Write header into file
  std::ofstream file("trax", std::ios::out | std::ios::trunc | std::ios::binary);
  
  file << file_header.signature;
  file << file_header.active_player;
  file << file_header.minX;
  file << file_header.minY;
  file << file_header.maxX;
  file << file_header.maxY;

  // Write each line of the board from (minX,minY) to (maxX,maxY) from left to right
  // Write tiles into file
  // TODO Change active_player each turn
  BoardTiles board_tiles;
  
  // Active player = White, set already
  board_tiles.side = 1;
  board_tiles.top_color = 2;

  file << board_tiles.side;
  file << board_tiles.top_color;

  // Active player = Red
  file_header.active_player = 2;
  // Sets position to offset 4 for active player in binary file
  file.seekp(4);
  file << file_header.active_player;
  // Sets position to where it left off
  file.seekp(11);

  board_tiles.side = 1;
  board_tiles.top_color = 2;
  
  file << board_tiles.side;
  file << board_tiles.top_color;

  board_tiles.side = 1;
  board_tiles.top_color = 2;

  file << board_tiles.side;
  file << board_tiles.top_color;

  board_tiles.side = 1;
  board_tiles.top_color = 2;

  file << board_tiles.side;
  file << board_tiles.top_color;


  return 0;
}