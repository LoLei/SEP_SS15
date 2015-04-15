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

//------------------------------------------------------------------------------
Addtile::Addtile() : Command("Addtile")
{
}

//------------------------------------------------------------------------------
int Addtile::execute(Game& board, std::vector<string>& params)
{
  return 0;
}

//------------------------------------------------------------------------------
void Addtile::setMaximas(Position reference)
{
  if(reference.getX() > max_x_)
  {
    max_x_ = reference.getX();
  }
  if(reference.getY() > max_y_)
  {
    max_y_ = reference.getY();
  }
  if(reference.getX() < min_x_)
  {
    min_x_ = reference.getX();
  }
  if(reference.getY() < min_y_)
  {
    min_y_ = reference.getY();
  }
}

//------------------------------------------------------------------------------
bool Addtile::valideInput(string user_input, Tile &tile, Position &position)
{
  try
  {
    string str3 = user_input.substr(user_input.find_first_of("("),
                                    user_input.find_last_of(")") -
                                    user_input.find_first_of("(") + 1);
    bool one_type = (user_input.find_last_of("+\\/") ==
              user_input.find_first_of("+\\/"));
    if(position.parse(str3) && one_type)
    {
      char tile_type = user_input.at(user_input.find_last_of("+\\/"));
      tile.setType(tile_type);
    }
    else
    {
      cout << "Invalid parameters" << endl;
      return false;
    }
  }
  catch(...)
  {
    cout << "Error: Wrong parameter count!" << endl;
    return false;
  }
  return true;
}

//------------------------------------------------------------------------------
void Addtile::addNewTile(string user_input, std::map<Position*, Tile*> &karte,
                         int &tile_counter)
{

  Position p1;
  Tile t1(Tile::EMPTY_T, COLOR_RED);
  // look up if the userinput is correct
  if(!(valideInput(user_input,t1,p1)))
  {
    return;
  }
  Tile empty_tile(Tile::EMPTY_T,EMPTY_C);
  // number of tiles beside the setted tile

  setMaximas(p1);
  Position center(0,0);
  if((tile_counter == 0) && (t1.getColor() != COLOR_RED || p1 != center))
  {
    cout << "Invalid coordinates - first tile must be set on (0,0)";
    cout << endl;
    return;
  }
  if(tile_counter)
  {
    adaptTile(karte, t1, p1);
  }

  for(auto& x: karte)
  {
    if(*x.first == p1 && *x.second != empty_tile)
    {
      cout << "Invalid coordinates - field not empty" << endl;
      return;
    }
  }

  bool replace = true;
  for(auto& y: karte)
  {
    if(*y.first == p1 && *y.second == empty_tile)
    {
      karte[y.first] = new Tile(t1);
      replace = false;
    }
  }
  if(replace)
  {
    karte.emplace(new Position(p1),new Tile(t1));
  }
  tile_counter++;

  if(tile_counter > 2)
  {
    fillEmptyTiles(karte);
  }
}

//------------------------------------------------------------------------------
bool Addtile::abfrage(bool abfrage1, bool &twisted, bool &lonely_tile, Tile &t1)
  {
    lonely_tile = false;
    if(abfrage1)
      {
        if(twisted)
        {
          cout << "Invalid move - connected line colors mismatch" << endl;
          return false;
        }
        t1.setColor(t1.notTopColor());
        twisted = true;
      }
      else
      {
        twisted = true;
      }
    return true;
  }

//------------------------------------------------------------------------------
bool Addtile::adaptTile(std::map<Position*, Tile*> karte, 
                        Tile &t1, Position p1)
{
  Tile empty_tile(Tile::EMPTY_T,EMPTY_C);
  // true wenn das tile angepasst wurde bzw schon richtig gelegen ist
  bool twisted = false;
  // falls angrenzend ein stein liegt
  bool lonely_tile = true;
  // positionen um den gelegten stein
  Position left(p1.getX() - 1,p1.getY());
  Position right(p1.getX() + 1,p1.getY());
  Position top(p1.getX(),p1.getY() - 1);
  Position buttom(p1.getX(),p1.getY() + 1);
  for(auto& x: karte)
  {
    if(*x.second == empty_tile)
    {
      continue;
    }
    if(*(x.first) == left &&
       !abfrage(x.second->getColorRight() != t1.getColorLeft(),
                twisted, lonely_tile, t1))
    {
      return false;
    }
    else if(*(x.first) == right &&
       !abfrage(x.second->getColorLeft() != t1.getColorRight(),
                twisted, lonely_tile, t1))
    {
      return false;
    }
    else if(*(x.first) == top &&
       !abfrage(x.second->getColorButtom() != t1.getColorTop(),
                twisted, lonely_tile, t1))
    {
      return false;
    }
    else if(*(x.first) == buttom &&
       !abfrage(x.second->getColorTop() != t1.getColorButtom(),
                twisted, lonely_tile, t1))
    {
      return false;
    }
    else
    {
      continue;
    }
  }
  if(lonely_tile)
  {
    cout << "Invalid coordinates - field not connected to tile" << endl;
    return false;
  }
  return true;
}

//------------------------------------------------------------------------------
bool Addtile::completeMap(std::map<Position*, Tile*> &karte, 
                          int &tile_counter, string &forAddtile)
{
  Tile empty_tile(Tile::EMPTY_T,EMPTY_C);
  for(auto& y: karte)
  {
    if(*y.second == empty_tile)
    {
      int found_tile = 0;
      Color Li = EMPTY_C;
      Color Re = EMPTY_C;
      Color Ob = EMPTY_C;
      Color Un = EMPTY_C;
      
      Position p1 = *(y.first);
      Position *left = new Position(p1.getX() - 1,p1.getY());
      Position *right = new Position(p1.getX()+1,p1.getY());
      Position *top = new Position(p1.getX(),p1.getY()-1);
      Position *buttom = new Position(p1.getX(),p1.getY()+1);
      for(auto& x: karte)
      {
        if(*x.second != empty_tile)
        {
          if(*(x.first) == *left)
          {
            found_tile++;
            Li = x.second->getColorRight();
          }
          else if(*(x.first) == *right)
          {
            found_tile++;
            Re = x.second->getColorLeft();
          }
          else if(*(x.first) == *top)
          {
            found_tile++;
            Ob = x.second->getColorButtom();
          }
          else if(*(x.first) == *buttom)
          {
            found_tile++;
            Un = x.second->getColorTop();
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
      if(found_tile > 2)
      {
        Tile neu(Li, Re, Ob, Un);
        forAddtile = "addtile " + y.first->toString() + " " + neu.getTypeOut();
        return true;
      }
    }
  }
  return false;
}

//------------------------------------------------------------------------------
void Addtile::fillEmptyTiles(std::map<Position*, Tile*> &karte)
{
  Tile empty_tile(Tile::EMPTY_T,EMPTY_C);
  bool wenn;
  for(signed int x = min_x_; x <= max_x_; x++)
  {
    for(signed int y = min_y_; y <= max_y_; y++)
    {
      wenn = true;
      Position pos1(x,y);
      for(auto& x: karte)
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