#include <iostream>
#include <cstdint>

#define TYPE 1480675924 // Ist BM, sollte sein TRAX

int main()
{
  
    uint32_t signature; // char[4] // TRAX // hex: 54 52 41 58 // little endian: 58 41 52 54
    signature = TYPE;

    std::cout << signature;
   




  return 0;
}