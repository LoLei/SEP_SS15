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
bool Addtile::valideInput(std::vector<string> v, Tile &tile, Position &position)
{
  if(v.size() != 3)
  {
    cout << "Error: Wrong parameter count!" << endl;
    return false;
  }
  if(position.parse(v[1]))
  {
    try
    {
      tile.setType(v[2][0]);
    }
    catch(...)
    {
      cout << "Invalid parameters" << endl;
      return false;
    }
  }
  else
  {
    cout << "Invalid parameters" << endl;
    return false;
  }

  /*
  try
  {
    string string_position = user_input.substr(user_input.find_first_of("("),
                                    user_input.find_last_of(")") -
                                    user_input.find_first_of("(") + 1);
    bool one_type = (user_input.find_last_of("+\\/") ==
              user_input.find_first_of("+\\/"));
    if(position.parse(string_position) && one_type)
    {
      try
      {
        char tile_type = user_input.at(user_input.find_last_of("+\\/"));
        tile.setType(tile_type);
      }
      catch(...)
      {
        cout << "Invalid parameters" << endl;
        return false;
      }
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
  */
  return true;
}

//------------------------------------------------------------------------------
int Addtile::addNewTile(std::vector<string> user_input, std::map<Position*, Tile*> &karte,
                         int &tile_counter, Color active_player)
{
  //für das autom. ergänzen
  if(tile_counter == 64)
  {
    cout << "Invalid move - not enough tiles left" << endl;
    return 3;
  }

  Position p1;
  Tile t1(Tile::EMPTY_T, COLOR_RED);
  t1.setPlayer(active_player);
  // look up if the userinput is correct
  if(!(valideInput(user_input,t1,p1)))
  {
    return 1;
  }
  Tile empty_tile(Tile::EMPTY_T,EMPTY_C);
  // number of tiles beside the setted tile

  Position center(0,0);
  if((tile_counter == 0) && (t1.getColor() != COLOR_RED || p1 != center))
  {
    cout << "Invalid coordinates - first tile must be set on (0,0)";
    cout << endl;
    return 2;
  }
  if(tile_counter && !adaptTile(karte, t1, p1))
  {
    return 2;
  }

  for(auto& x: karte)
  {
    if(*x.first == p1 && *x.second != empty_tile)
    {
      cout << "Invalid coordinates - field not empty" << endl;
      return 2;
    }
  }

  bool replace = true;
  for(auto& y: karte)
  {
    if(*y.first == p1 && *y.second == empty_tile)
    {
      delete y.second;
      karte[y.first] = new Tile(t1);
      replace = false;
    }
  }

  // tile einfügen
  if(replace)
  {
    karte.emplace(new Position(p1),new Tile(t1));
  }
  tile_counter++;

  // spielfeld vergrößern
  setMaximas(p1);

  // zwischenfelder mit leeren einträgen füllen
  if(tile_counter > 2)
  {
    fillEmptyTiles(karte);
  }

  // falls alles geklappt hatt
  return 0;
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
bool Addtile::completeMap(std::map<Position*, Tile*> &karte, std::vector<string> &forAddtile)
{
  Tile empty_tile(Tile::EMPTY_T,EMPTY_C);
  for(auto& y: karte)
  {
    if(*y.second != empty_tile)
    {
      continue;
    }
    int found_tile = 0;
    Color Li = EMPTY_C;
    Color Re = EMPTY_C;
    Color Ob = EMPTY_C;
    Color Un = EMPTY_C;

    Position p1 = *(y.first);
    Position left(p1.getX() - 1,p1.getY());
    Position right(p1.getX()+1,p1.getY());
    Position top(p1.getX(),p1.getY()-1);
    Position buttom(p1.getX(),p1.getY()+1);
    for(auto& x: karte)
    {
      if(*x.second == empty_tile)
      {
        continue;
      }
      if(*(x.first) == left)
      {
        found_tile++;
        Li = x.second->getColorRight();
      }
      else if(*(x.first) == right)
      {
        found_tile++;
        Re = x.second->getColorLeft();
      }
      else if(*(x.first) == top)
      {
        found_tile++;
        Ob = x.second->getColorButtom();
      }
      else if(*(x.first) == buttom)
      {
        found_tile++;
        Un = x.second->getColorTop();
      }
      else
      {
        continue;
      }
    }
    if(found_tile >= 2)
    {
      Tile neu(Li, Re, Ob, Un);
      if(neu == empty_tile)
      {
        continue;
      }
      forAddtile[1] = y.first->toString();
      forAddtile[2] = neu.getTypeOut();
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