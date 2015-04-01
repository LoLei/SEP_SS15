#include <iostream>
#include <fstream>

#define TYPE 1480675924 // TRAX in dec from hex in little endian

int main()
{
  typedef struct
  {
    char *signature; // char[4] // TRAX // hex: 54 52 41 58 // little endian: 58 41 52 54
    char active_player; // char // white (1) or red (2)
    signed char minX; // signed char
    signed char minY; // signed char
    signed char maxX; // signed char
    signed char maxY; // signed char
  } BoardHeader; // signed char

  typedef struct
  {
    char side; // char // no figure (0), cross (1), Kurve1 "/" (2), Kurve2 "\" (3) // offset 0
    char top_color; // char // no figure (0), white end (1), red end (2) // offset 1
  } BoardTiles;

  // Write values into header
  BoardHeader FileHeader;
  //FileHeader.signature = { 'T', 'R', 'A', 'X', '\0' };
  FileHeader.signature = "TRAX";
  FileHeader.active_player = 1;
  FileHeader.minX = 0;
  FileHeader.minY = 0;
  FileHeader.maxX = 10;
  FileHeader.maxY = 20;

  // Write header into file
  std::ofstream file("test", std::ios::out | std::ios::trunc | std::ios::binary);
  
  file << FileHeader.signature;
  file << FileHeader.active_player;
  file << FileHeader.minX;
  file << FileHeader.minY;
  file << FileHeader.maxX;
  file << FileHeader.maxY;

  // Write each line of the board from (minX,minY) to (maxX,maxY) from left to right
  // PSEUDO
  char num_1 = 1;
  char num_2 = 0;
  long pos = file.tellp();
  // Sets position to beginning of file
  pos = 0;
  // Sets position to next line in binary file
  file.seekp(pos+16);
  file << num_1;
  file << num_2;

  return 0;
}