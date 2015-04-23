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
AddTile::AddTile() : Command("Addtile")
{
  // empty tile as a member of addtile
  empty_tile_->setColor(EMPTY_C);
  empty_tile_->setType('0');
  empty_tile_->red_id_ = 0;
  empty_tile_->white_id_ = 0;
}

//------------------------------------------------------------------------------
AddTile::~AddTile()
{
}

//------------------------------------------------------------------------------
bool AddTile::valideInput(std::vector<string> user_input, Tile &tile,
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
int AddTile::execute(Game& board, std::vector<string>& user_input)
{
  // number of tiles beside the setted tile
  // for auto complete
  if(board.getNumberOfTiles() == 64)
  {
    cout << "Invalid move - not enough tiles left" << endl;
    return 3;
  }

  Position p1;
  Tile t1(Tile::EMPTY_T, COLOR_RED);

  t1.setPlayer(board.getActivePlayer());
  // look up if the userinput is correct
  if(!(valideInput(user_input,t1,p1)))
  {
    return 1;
  }

  t1.white_id_ = Tile::id_counter_++;
  t1.red_id_ = Tile::id_counter_++;

  Position center(0,0);
  if((board.getNumberOfTiles() == 0)
    && (t1.getColor() != COLOR_RED || p1 != center))
  {
    cout << "Invalid coordinates - first tile must be set on (0,0)";
    cout << endl;
    return 2;
  }

    for(auto& x: board.field)
  {
    if(*x.first == p1 && *x.second != *empty_tile_)
    {
      cout << "Invalid coordinates - field not empty" << endl;
      return 2;
    }
  }
  int code;
  if(board.getNumberOfTiles())
  {
    code = adaptTile(board.field, t1, p1);
  }
  if(code == 1)
  {
    return 2;
  }

  bool replace = true;
  for(auto& y: board.field)
  {
    if(*y.first == p1 && *y.second == *empty_tile_)
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

  // return 0 if nobody won 9 red 8 white
  if(int newcode = checkWin(board, t1))
  {
    return newcode;
  }

  if(code == 8)
  {
    cout << "Player white wins!" << endl;
    return code;
  }
  if(code == 9)
  {
    cout << "Player red wins!" << endl;
    return code;
  }

  // if nobody won and tiles are not available
  if(board.getNumberOfTiles() == 64)
  {
    cout << "No more tiles left. Game ends in a draw!" << endl;
    return 4;
  }

  // falls alles geklappt hatt
  return 0;
}

//------------------------------------------------------------------------------
bool AddTile::abfrage(bool abfrage1, bool &twisted, bool &lonely_tile, Tile &t1,
                      Color c1,Tile& t2, std::vector<int> &red_id_to_merge,
                      std::vector<int> &white_id_to_merge)
{
  //cout << t1.red_id_ << t2.red_id_ << t1.white_id_ << t2.white_id_ << endl;
  lonely_tile = false;
  if(abfrage1)
  {
    if(twisted)
    {
      cout << "Invalid move - connected line colors mismatch" << endl;
      return false;
    }
    t1.setColor(t1.notTopColor());
    if(c1 == COLOR_WHITE)
    {
      t1.red_id_ = t2.red_id_;
      red_id_to_merge.push_back(t1.red_id_);
    }
    if(c1 == COLOR_RED)
    {
      t1.white_id_ = t2.white_id_;
      white_id_to_merge.push_back(t1.white_id_);
    }
    twisted = true;
  }
  else
  {
    if(c1 == COLOR_RED)
    {
      t1.red_id_ = t2.red_id_;
      red_id_to_merge.push_back(t1.red_id_);
    }
    if(c1 == COLOR_WHITE)
    {
      t1.white_id_ = t2.white_id_;
      white_id_to_merge.push_back(t1.white_id_);
    }
    twisted = true;
  }
  //cout << t1.red_id_ << t2.red_id_ << t1.white_id_ << t2.white_id_ << endl;
  return true;
}



//------------------------------------------------------------------------------
int AddTile::adaptTile(std::map<Position*, Tile*> karte,
                        Tile &t1, Position p1)
{
  // true wenn das tile angepasst wurde bzw schon richtig gelegen ist
  bool twisted = false;
  // falls angrenzend ein stein liegt
  bool lonely_tile = true;
  // positionen um den gelegten stein
  Position left(p1.getX() - 1,p1.getY());
  Position right(p1.getX() + 1,p1.getY());
  Position top(p1.getX(),p1.getY() - 1);
  Position buttom(p1.getX(),p1.getY() + 1);

  std::vector<int> red_id_to_merge;
  std::vector<int> white_id_to_merge;

  for(auto& x: karte)
  {
    if(*x.second == *empty_tile_)
    {
      continue;
    }
    if(*(x.first) == left &&
       !abfrage(x.second->getColorRight() != t1.getColorLeft(),
                twisted, lonely_tile, t1, t1.getColorLeft(),*x.second,
                red_id_to_merge, white_id_to_merge))
    {
      return 1;
    }
    else if(*(x.first) == right &&
       !abfrage(x.second->getColorLeft() != t1.getColorRight(),
                twisted, lonely_tile, t1,t1.getColorRight(),*x.second,
                red_id_to_merge, white_id_to_merge))
    {
      return 1;
    }
    else if(*(x.first) == top &&
       !abfrage(x.second->getColorButtom() != t1.getColorTop(),
                twisted, lonely_tile, t1,t1.getColorTop(),*x.second,
                red_id_to_merge, white_id_to_merge))
    {
      return 1;
    }
    else if(*(x.first) == buttom &&
       !abfrage(x.second->getColorTop() != t1.getColorButtom(),
                twisted, lonely_tile, t1,t1.getColorButtom(),*x.second,
                red_id_to_merge, white_id_to_merge))
    {
      return 1;
    }
    else
    {
      continue;
    }
  }

 /*cout << "(" << red_id_to_merge.size() << ") ";
 for(int i = 0; i < red_id_to_merge.size(); i++)
 {
   cout << red_id_to_merge[i] << " ";
 }
 cout << endl;

  cout << "(" << white_id_to_merge.size() << ") ";
 for(int i = 0; i < white_id_to_merge.size(); i++)
 {
   cout << white_id_to_merge[i] << " ";
 }
 cout << endl;*/

  if(red_id_to_merge.size() >= 2)
  {
    for(auto& x: karte)
    {
      if(x.second->red_id_ == red_id_to_merge[1])
      {
        x.second->red_id_ = red_id_to_merge[0];
      }
    }
    if(t1.red_id_ == red_id_to_merge[1])
    {
      t1.red_id_ = red_id_to_merge[0];
    }
    if(red_id_to_merge[1] == red_id_to_merge[0])
    {
      return 9;
      //win
    }
  }
  if(white_id_to_merge.size() >= 2)
  {
    for(auto& x: karte)
    {
      if(x.second->white_id_ == white_id_to_merge[1])
      {
        x.second->white_id_ = white_id_to_merge[0];
      }
    }
    if(t1.white_id_ == white_id_to_merge[1])
    {
      t1.white_id_ = white_id_to_merge[0];
    }
    if(white_id_to_merge[0] == white_id_to_merge[1])
    {
      return 8;
      //win
    }
  }


  if(lonely_tile)
  {
    cout << "Invalid coordinates - field not connected to tile" << endl;
    return 1;
  }
  return 0;
}

//------------------------------------------------------------------------------
bool AddTile::completeMap(std::map<Position*, Tile*> &karte,
  std::vector<string> &forAddtile)
{
  for(auto& y: karte)
  {
    if(*y.second != *empty_tile_)
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
      if(*x.second == *empty_tile_)
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
      if(neu == *empty_tile_)
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
void AddTile::fillEmptyTiles(Game& board)
{
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
        board.field.emplace(new Position(empty_position),new Tile(*empty_tile_));
      }
    }
  }
}

//------------------------------------------------------------------------------
int AddTile::checkWin(Game& board, Tile t1)
{
  if(winLength(board,t1,"white"))
  {
    return 8;
  }
  if(winLength(board,t1,"red"))
  {
    return 9;
  }
  return 0;
}

//------------------------------------------------------------------------------
int AddTile::winLength(Game& board, Tile t1, string color)
{
  // if white line goes over 8 lines or columns
  signed int min_x = 0;
  signed int min_y = 0;
  signed int max_x = 0;
  signed int max_y = 0;
  for(auto& x: board.field)
  {
    if(x.second->getId(color) == t1.getId(color))
    {
      if(+x.first->getX() > max_x)
      {
        max_x = +x.first->getX();
      }
      if(+x.first->getY() > max_y)
      {
        max_y = +x.first->getY();
      }
      if(+x.first->getX() < min_x)
      {
        min_x = +x.first->getX();
      }
      if(+x.first->getY() < min_y)
      {
        min_y = +x.first->getY();
      }
    }
    if(max_x - min_x >= 7 || max_y - min_y >= 7)
    {
      cout << "Player " << color << " wins!" << endl;
      return 1;
    }
  }
  return 0;
}