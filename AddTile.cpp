//------------------------------------------------------------------------------
// AddTile.cpp
//
// Group: Group 11574, study assistant Philip Loibl
//
// Authors: 
// Markus Pichler 1331070
//------------------------------------------------------------------------------
//

#include "AddTile.h"

using std::cout;
using std::endl;
using std::string;

//------------------------------------------------------------------------------
// Constructor
//
Addtile::Addtile() : Command("Addtile")
{
}

//------------------------------------------------------------------------------
Addtile::~Addtile()
{
}

//------------------------------------------------------------------------------
bool Addtile::valideInput(std::vector<string> user_input, Tile &tile,
  Position &position)
{
  if(user_input.size() != 3)
  {
    cout << "Error: Wrong parameter count!" << endl;
    return false;
  }
  if(position.parse(user_input[1]))
  {
    try
    {
      tile.setType(user_input[2][0]);
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
  return true;
}

//------------------------------------------------------------------------------
int Addtile::execute(Game& board, std::vector<string>& user_input)
{
  //für das autom. ergänzen
  if(board.getNumberOfTiles() == 64)
  {
    cout << "Invalid move - not enough tiles left" << endl;
    return 3;
  }

  Position p1;
  Tile t1(Tile::EMPTY_T, COLOR_RED);
  t1.white_id_ = Tile::id_counter_++;
    t1.red_id_ = Tile::id_counter_++;
  t1.setPlayer(board.getActivePlayer());
  // look up if the userinput is correct
  if(!(valideInput(user_input,t1,p1)))
  {
    return 1;
  }
  Tile empty_tile(Tile::EMPTY_T,EMPTY_C);
  // number of tiles beside the setted tile

  Position center(0,0);
  if((board.getNumberOfTiles() == 0)
    && (t1.getColor() != COLOR_RED || p1 != center))
  {
    cout << "Invalid coordinates - first tile must be set on (0,0)";
    cout << endl;
    return 2;
  }
  if(board.getNumberOfTiles() && !adaptTile(board.field, t1, p1))
  {
    return 2;
  }

  for(auto& x: board.field)
  {
    if(*x.first == p1 && *x.second != empty_tile)
    {
      cout << "Invalid coordinates - field not empty" << endl;
      return 2;
    }
  }

  bool replace = true;
  for(auto& y: board.field)
  {
    if(*y.first == p1 && *y.second == empty_tile)
    {
      delete y.second;
      board.field[y.first] = new Tile(t1);
      //y.second->white_id_ = Tile::id_counter_++;
      //y.second->red_id_ = Tile::id_counter_++;
      replace = false;
    }
  }

  // tile einfügen
  if(replace)
  {
    board.field.emplace(new Position(p1),new Tile(t1));
  }
  board.riseNumberOfTiles();

  // spielfeld vergrößern
  board.setMaximas(p1);

  // zwischenfelder mit leeren einträgen füllen
  if(board.getNumberOfTiles() > 2)
  {
    fillEmptyTiles(board);
  }

  // falls alles geklappt hatt
  return 0;
}

//------------------------------------------------------------------------------
bool Addtile::abfrage(bool abfrage1, bool &twisted, bool &lonely_tile, Tile &t1,
                      Color c1,Tile& t2)
  {
    cout << t1.red_id_ << t2.red_id_ << t1.white_id_ << t2.white_id_ << endl;
    lonely_tile = false;
    if(abfrage1)
      {
        if(twisted)
        {
          cout << "Invalid move - connected line colors mismatch" << endl;
          return false;
        }
        t1.setColor(t1.notTopColor());
        if(c1 == COLOR_RED)
        {
          t1.red_id_ = t2.red_id_;
        }
        if(c1 == COLOR_WHITE)
        {
          t1.white_id_ = t2.white_id_;
        }
        twisted = true;
      }
      else
      {
        if(c1 == COLOR_RED)
        {
          t1.red_id_ = t2.red_id_;
        }
        if(c1 == COLOR_WHITE)
        {
          t1.white_id_ = t2.white_id_;
        }
        twisted = true;
      }
    cout << t1.red_id_ << t2.red_id_ << t1.white_id_ << t2.white_id_ << endl;
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
                twisted, lonely_tile, t1, t1.getColorLeft(),*x.second))
    {
      return false;
    }
    else if(*(x.first) == right &&
       !abfrage(x.second->getColorLeft() != t1.getColorRight(),
                twisted, lonely_tile, t1,t1.getColorRight(),*x.second))
    {
      return false;
    }
    else if(*(x.first) == top &&
       !abfrage(x.second->getColorButtom() != t1.getColorTop(),
                twisted, lonely_tile, t1,t1.getColorTop(),*x.second))
    {
      return false;
    }
    else if(*(x.first) == buttom &&
       !abfrage(x.second->getColorTop() != t1.getColorButtom(),
                twisted, lonely_tile, t1,t1.getColorButtom(),*x.second))
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
  std::vector<string> &forAddtile)
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
void Addtile::fillEmptyTiles(Game& board)
{
  Tile empty_tile(Tile::EMPTY_T,EMPTY_C);
  bool wenn;
  for(signed int x = board.min_x_; x <= board.max_x_; x++)
  {
    for(signed int y = board.min_y_; y <= board.max_y_; y++)
    {
      wenn = true;
      Position empty_position(x,y);
      for(auto& x: board.field)
      {
        if(*x.first == empty_position)
        {
          wenn = false;
          break;
        }
      }
      if(wenn)
      {
        board.field.emplace(new Position(empty_position),new Tile(empty_tile));
      }
    }
  }
}