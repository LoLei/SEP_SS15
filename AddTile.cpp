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

using std::cout;
using std::endl;
using std::string;

Addtile::Addtile() : Command("Addtile")
{
}

int Addtile::execute(Game& board, std::vector<string>& params)
{
  return 0;
}

/*
//------------------------------------------------------------------------------
bool Addtile::valuecommand(string user_input, Tile &tile,
                           Position &position, const Color color)
{
  try
  {
    string str1 = user_input.substr(user_input.find_first_of("("),user_input.find_last_of(")") - user_input.find_first_of("(") + 1);
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
  catch(...)
  {
    std::cout << "Error: Wrong parameter count!" << std::endl;
    return false;
  }
}
*/

//------------------------------------------------------------------------------
void Addtile::addNewTile(string user_input, std::map<Position*, Tile*> &karte,
                         int &tile_counter)
{
  cout << tile_counter << endl;
  Position p1;
  Position center(0,0);
  Tile starttile(Tile::TYPE_CROSS, COLOR_WHITE);
  try
  {
    string str3 = user_input.substr(user_input.find_first_of("("),
                                    user_input.find_last_of(")") -
                                    user_input.find_first_of("(") + 1);
    bool one_type = (user_input.find_last_of("+\\/") ==
              user_input.find_first_of("+\\/"));
    if(p1.parse(str3) && one_type)
    {
      char tile_type = user_input.at(user_input.find_last_of("+\\/"));

      Tile t1(Tile::TYPE_CROSS, COLOR_WHITE);
      t1.charToType(tile_type),COLOR_WHITE;

      bool ok = true;
      bool twist = false;
      bool found_tile = true;

      if((tile_counter == 0) && (t1 != starttile || p1 != center))
      {
        ok = false;
        cout << "Invalid coordinates - first tile must be set on (0,0)";
        cout << endl;
      }
      if(tile_counter)
      {
        found_tile = false;
        Position *left = new Position(p1.getX() - 1,p1.getY());
        Position *right = new Position(p1.getX()+1,p1.getY());
        Position *top = new Position(p1.getX(),p1.getY()-1);
        Position *buttom = new Position(p1.getX(),p1.getY()+1);
        for (auto& x: karte)
        {
          if(*(x.first) == *left)
          {
            found_tile = true;
            if(x.second->getColorRight() != t1.getColorLeft() && ok)
            {
              if(twist)
                ok = false;
              t1.setColor(t1.notTopColor());
              twist = true;
            }
          }
          if(*(x.first) == *right)
          {
            found_tile = true;
            if(x.second->getColorLeft() != t1.getColorRight() && ok)
            {
              if(twist)
                ok = false;
              t1.setColor(t1.notTopColor());
              twist = true;
            }
          }
          if(*(x.first) == *top)
          {
            found_tile = true;
            if(x.second->getColorButtom() != t1.getColorTop() && ok)
            {
              if(twist)
                ok = false;
              t1.setColor(t1.notTopColor());
              twist = true;
            }
          }
          if(*(x.first) == *buttom)
          {
            found_tile = true;
            if(x.second->getColorTop() != t1.getColorButtom() && ok)
            {
              if(twist)
                ok = false;
              t1.setColor(t1.notTopColor());
              twist = true;
            }
          }
        }
        delete left;
        delete right;
        delete top;
        delete buttom;
      }
      if(ok && found_tile)
      {
        karte.emplace(new Position(p1.getX(),p1.getY()),new Tile(t1));
        tile_counter++;
      }
    }
    else
    {
      cout << "Invalid parameters(addtile)" << endl;
    }
  }
  catch(...)
  {
    cout << "Error: Wrong parameter count!" << endl;
  }
}