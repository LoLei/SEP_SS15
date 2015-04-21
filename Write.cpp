//------------------------------------------------------------------------------
// Filename: Write.cpp
// Description: Used for writing binary file
//              First only as write command
//              Later as automatic write if -g flag is set
// Authors: Lorenz Leitner
// Tutor: Philipp Loibl
// Group: 11574
// Created: 14.04.2015
// Last change: 14.04.2015
//------------------------------------------------------------------------------

#include "Write.h"

Write::Write() : Command("Write")
{
}

int Write::execute(Game& board, std::vector<std::string>& params)
{
  return 0;
}

//------------------------------------------------------------------------------
void Write::createNewFile(std::string file_name, std::map<Position*, Tile*> &karte,
  int &tile_counter, Color active_player, int &error_set)
{
  if (!((tile_counter == 0) && (error_set == 1)))
  {
    //std::string file_name;
    try
    {
      // Takes parameter after write as file_name
      //file_name = user_input.substr(6);
      std::streamoff pos;

      class FileHeader
      {
      public:
        char *signature;    // char[4] // TRAX
        char active_player; // char // white (1) or red (2)
        signed char minX;   // s8
        signed char minY;   // s8
        signed char maxX;   // s8
        signed char maxY;   // s8
      };

      class BoardTiles
      {
      public:
        char side;      // no figure (0), cross (1), Kurve1 "/" (2), Kurve2 "\" (3)
        char top_color; // no figure (0), white end (1), red end (2) // offset 1
      };

      FileHeader file_header;
      //--------------------------------------------------------------------------
      // Write values into header
      // Find max and min coordinates
      // Min
      file_header.minX = Addtile::min_x_;
      file_header.minY = Addtile::min_y_;
      // Max
      file_header.maxX = Addtile::max_x_;
      file_header.maxY = Addtile::max_y_;
      // Signature and active player
      file_header.signature = "TRAX";
      file_header.active_player = active_player;

      // Open file for writing
      // file_name is either argv[2] or command after write, i.e. user_input
      std::ofstream file(file_name,
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

      //--------------------------------------------------------------------------//
      // Write each line of the board from (minX,minY) to (maxX,maxY)
      // from left to right, top to bottom
      // Write tiles into file
      BoardTiles board_tiles;

      // Write
      for (signed int y = Addtile::min_y_; y <= Addtile::max_y_; y++)
      {
        for (signed int x = Addtile::min_x_; x <= Addtile::max_x_; x++)
        {
          Position pos1(x, y);
          for (auto& x : karte)
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
    }
    //------------------------------------------------------------------------------
    catch (WriteException& e1)
    {
      std::cout << e1.what() << file_name << std::endl;
    }
    catch (...)
    {
      std::cout << "Error: Wrong parameter count!" << std::endl;
    }
  }
}