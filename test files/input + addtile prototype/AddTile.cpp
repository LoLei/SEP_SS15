//------------------------------------------------------------------------------
// Filename: AddTile.cpp
// Description: ...
// Authors: Pichler
// Tutor: Philipp Loibl
// Group: 11574
// Created: 01.04.2015
// Last change: 01.04.2015
//------------------------------------------------------------------------------

#include "AddTile.h"


Addtile::Addtile() : Command("Addtile")
{
  //
}

int Addtile::execute(Game& board, std::vector<std::string>& params)
{
  return 0;
}

//------------------------------------------------------------------------------
bool Addtile::valuecommand(std::string user_input, Tile &tile, 
                           Position &position, const Color color)
{
  try
  {
    std::string str1 = user_input.substr(user_input.find_first_of("("),user_input.find_last_of(")") - user_input.find_first_of("(") + 1);
    if (position.parse(str1))
    {
      tile.setType(user_input.at(user_input.find_last_of("+\\/")));
      tile.setColor(color);
      std::cout << "Position: " << position.toString() << " Color: " << tile.getColorOut() << " Type: " << tile.getTypeOut() << std::endl;
      return true;
    }
    else
    {
      std::cout << "Invalid parameters" << std::endl;
      return false;
    }
  }
  catch(std::exception& e)
  {
  return false;
  }
}