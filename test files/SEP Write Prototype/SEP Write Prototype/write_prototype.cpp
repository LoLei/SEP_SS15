#include <iostream>
#include <cstdint>

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




  return 0;
}