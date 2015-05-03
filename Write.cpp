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

#include "Write.h"

//------------------------------------------------------------------------------
Write::Write() : Command("Write")
{
}

//------------------------------------------------------------------------------
Write::~Write()
{
}

//------------------------------------------------------------------------------
int Write::execute(Game& board, std::vector<std::string>& user_input)
{
  try
  {
    // case: filename without whitespace!
    if(user_input.size() != 2)
    {
      throw WrongParameterException();
    }
    std::string file_name = user_input[1];
    try
    {
      //--------------------------------------------------------------------------
      // FileHeader Class
      // Simple struct replacement for easier reading of file variables
      // File header information in binary file
      //
      class FileHeader
      {
      public:
        char *signature_;    // char[4] // TRAX
        char active_player_; // char // white (1) or red (2)
        signed char minim_x_;   // s8
        signed char minim_y_;   // s8
        signed char maxim_x_;   // s8
        signed char maxim_y_;   // s8
      };

      //--------------------------------------------------------------------------
      // BoardTiles Class
      // Simple struct replacement for easier reading of file variables
      // Actual tiles in binary file
      //
      class BoardTiles
      {
      public:
        char side;    // no figure (0), cross (1), Kurve1 "/" (2), Kurve2 "\" (3)
        char top_color; // no figure (0), white end (1), red end (2) // offset 1
      };

      FileHeader file_header;
      //--------------------------------------------------------------------------
      // Write values into header
      // Find max and min coordinates
      file_header.minim_x_ = board.min_x_;
      file_header.minim_y_ = board.min_y_;
      file_header.maxim_x_ = board.max_x_;
      file_header.maxim_y_ = board.max_y_;
      // Signature and active player;
      file_header.signature_ = /*static_cast<char*>*/("TRAX");
      file_header.active_player_ = board.getActivePlayer();

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
      file << file_header.signature_;
      file << file_header.active_player_;
      file << file_header.minim_x_;
      file << file_header.minim_y_;
      file << file_header.maxim_x_;
      file << file_header.maxim_y_;

      //--------------------------------------------------------------------------
      // Write each line of the board
      // from (minim_x_,minim_y_) to (maxim_x_,maxim_y_)
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
    }
    //----------------------------------------------------------------------------
    catch (WriteException& e1)
    {
      std::cout << e1.what() << file_name << std::endl;
    }
    catch (...)
    {
      throw WrongParameterException();
    }
    return 0;
  }
  catch (WrongParameterException& e1)
  {
    std::cout << e1.what() << std::endl;
    return 1;
  }
}