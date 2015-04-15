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

  signed int Addtile::max_x_ = 0;
  signed int Addtile::max_y_ = 0;
  signed int Addtile::min_x_ = 0;
  signed int Addtile::min_y_ = 0;

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

  Position p1;
  Position center(0,0);
  Tile empty_tile(Tile::EMPTY_T,EMPTY_C);
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
      // Won't compile otherwise
      Tile t1(Tile::EMPTY_T, COLOR_RED);
      t1.setType(tile_type);
      bool ok = true;
      bool twisted = false;
      int found_tile = 1;

      if(p1.getX() > max_x_)
      {
        max_x_ = p1.getX();
      }
      if(p1.getY() > max_y_)
      {
        max_y_ = p1.getY();
      }
      if(p1.getX() < min_x_)
      {
        min_x_ = p1.getX();
      }
      if(p1.getY() < min_y_)
      {
        min_y_ = p1.getY();
      }

      if((tile_counter == 0) && (t1.getColor() != COLOR_RED || p1 != center))
      {
        ok = false;
        cout << "Invalid coordinates - first tile must be set on (0,0)";
        cout << endl;
      }
      if(tile_counter)
      {
        found_tile = 0;
        Position *left = new Position(p1.getX() - 1,p1.getY());
        Position *right = new Position(p1.getX()+1,p1.getY());
        Position *top = new Position(p1.getX(),p1.getY()-1);
        Position *buttom = new Position(p1.getX(),p1.getY()+1);
        for (auto& x: karte)
        {
          if(*x.second != empty_tile)
          {
            if(*(x.first) == *left)
            {
              found_tile++;
              if(x.second->getColorRight() != t1.getColorLeft())
              {
                if(ok)
                {
                  if(twisted)
                  {
                    ok = false;
                    break;
                  }
                  t1.setColor(t1.notTopColor());
                  twisted = true;
                }
              }
              else
              {
                twisted = true;
              }
            }
            else if(*(x.first) == *right)
            {
              found_tile++;
              if(x.second->getColorLeft() != t1.getColorRight())
              {
                if(ok)
                {
                  if(twisted)
                  {
                    ok = false;
                    break;
                  }
                  t1.setColor(t1.notTopColor());
                  twisted = true;
                }
              }
              else
              {
                twisted = true;
              }
            }
            else if(*(x.first) == *top)
            {
              found_tile++;
              if(x.second->getColorButtom() != t1.getColorTop())
              {
                if(ok)
                {
                  if(twisted)
                  {
                    ok = false;
                    break;
                  }
                  t1.setColor(t1.notTopColor());
                  twisted = true;
                }
              }
              else
              {
                twisted = true;
              }
            }
            else if(*(x.first) == *buttom)
            {
              found_tile++;
              if(x.second->getColorTop() != t1.getColorButtom())
              {
                if(ok)
                {
                  if(twisted)
                  {
                    ok = false;
                    break;
                  }
                  t1.setColor(t1.notTopColor());
                  twisted = true;
                }
              }
              else
              {
                twisted = true;
              }
            }
            else
            {
              continue;
            }
          }
        }
        delete left;
        delete right;
        delete top;
        delete buttom;
      }
      if(ok)
      {
        for (auto& x: karte)
        {
          if(*x.first == p1 && *x.second != empty_tile)
          {
            ok = false;
            cout << "Invalid coordinates - field not empty" << endl;
          }
        }
      }
      else if(tile_counter != 0)
      {
        cout << "Invalid move - connected line colors mismatch" << endl;
      }
      if(ok &&(found_tile == 0))
      {
        cout << "Invalid coordinates - field not connected to tile" << endl;
      }
      if(ok && found_tile)
      {
        karte.emplace(new Position(p1),new Tile(t1));
        tile_counter++;
      }

      if(tile_counter > 2)
      {
        fillEmptyTiles(karte);
      }
    }
    else
    {
      cout << "Invalid parameters" << endl;
    }
  }
  catch(...)
  {
    cout << "Error: Wrong parameter count!" << endl;
  }
}

//------------------------------------------------------------------------------
bool Addtile::completeMap(std::map<Position*, Tile*> &karte, int &tile_counter string &forAddtile)
{
  std::map<Position*, int> grenzTiles;
  Tile empty_tile(Tile::EMPTY_T,EMPTY_C);
  for (auto& y: karte)
  {
    if(*y.second == empty_tile)
    {
      int found_tile = 0;
      Position p1 = *(y.first);
      Position *left = new Position(p1.getX() - 1,p1.getY());
      Position *right = new Position(p1.getX()+1,p1.getY());
      Position *top = new Position(p1.getX(),p1.getY()-1);
      Position *buttom = new Position(p1.getX(),p1.getY()+1);
      for (auto& x: karte)
      {
        if(*(x.first) == *left)
        {
          found_tile++;
        }
        else if(*(x.first) == *right)
        {
          found_tile++;
        }
        else if(*(x.first) == *top)
        {
          found_tile++;
        }
        else if(*(x.first) == *buttom)
        {
          found_tile++;
        }
        else
        {
          continue;
        }
      }
      delete left;
      delete right;
      delete top;
      delete buttom;
      grenzTiles.emplace(new Position(p1),found_tile);
    }
  }
  // für testzwecke

  /*for (auto& x: grenzTiles)
  {
    //cout 
    cout << karte.find(x.first)->second->getColorOut() <<" "
         << karte.find(x.first)->second->getTypeOut() << endl;
  }*/

  for (auto& x: grenzTiles)
  {
    if(x.second > 2 && (*karte.find(x.first)->second != empty_tile))
    {
      cout << endl << "___ für testzwecke ___" << endl;
      cout << x.first->toString() << ": " << x.second << endl;
      cout << "ergänze tile in Position " << x.first->toString() << endl;
      cout << "___" << endl << endl;
      forAddtile = "addtile " + x.first->toString() + " " + karte.find(x.first)->second->getTypeOut();
      return true;
    }
  }

  return false;
}

//------------------------------------------------------------------------------
void Addtile::fillEmptyTiles(std::map<Position*, Tile*> &karte)
{
  Tile empty_tile(Tile::EMPTY_T,EMPTY_C);
  bool wenn;
  for(signed int x = min_x_; x < max_x_; x++)
  {
    for(signed int y = min_y_; y <= max_y_; y++)
    {
      wenn = true;
      Position pos1(x,y);
      for (auto& x: karte)
      {
        if(*x.first == pos1)
        {
          wenn = false;
          break;
        }
      }
      if(wenn)
      {
        karte.emplace(new Position(pos1),new Tile(empty_tile));
      }
    }
  }
}