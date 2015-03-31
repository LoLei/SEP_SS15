#include <iostream>
#include <cstdint>
#include <fstream>

#define TYPE 1480675924 // TRAX in dec from hex in little endian

int main()
{
  typedef struct
  {
    uint32_t signature; // char[4] // TRAX // hex: 54 52 41 58 // little endian: 58 41 52 54
    uint8_t active_player; // char // white (1) or red (2)
    int8_t minX; // signed char
    int8_t minY; // signed char
    int8_t maxX; // signed char
    int8_t maxY; // signed char
  } BoardHeader; // signed char

  typedef struct
  {
    uint8_t side; // char // no figure (0), cross (1), Kurve1 "/" (2), Kurve2 "\" (3)
    uint8_t top_color; // char // no figure (0), white end (1), red end (2)
  } BoardTiles;

  BoardHeader FileHeader;
  FileHeader.signature = TYPE;
  

  std::ofstream file("test", std::ios::out | std::ios::trunc | std::ios::binary);
  //file << FileHeader.signature;

  char sig[5] = "TRAX";
  file << sig;
  char a_p = 1;
  file << a_p;
  char min_x = 0;
  file << min_x;
  char min_y = 0;
  file << min_y;
  char max_x = 10;
  file << max_x;
  char max_y = 10;
  file << max_y;



  return 0;
}