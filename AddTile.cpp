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
}

//------------------------------------------------------------------------------
AddTile::~AddTile()
{
}

//------------------------------------------------------------------------------
bool AddTile::valideInput(std::vector<string> user_input, Tile &tile,
  Position &position)
{
  try
  {
    if (user_input.size() != 3)
    {
      cout << "Error: Wrong parameter count!" << endl;
      return false;
    }
    if (position.parse(user_input[1]))
    {
      try
      {
        tile.setType(user_input[2][0]);
      }
      catch (...)
      {
        throw InvalidParameterException();
      }
    }
    else
    {
      throw InvalidParameterException();
    }
    return true;
  }
  catch (InvalidParameterException& e1)
  {
    std::cout << e1.what() << std::endl;
    return false;
  }
  catch (WrongParameterException& e1)
  {
    std::cout << e1.what() << std::endl;
    return false;
  }
}

//------------------------------------------------------------------------------
int AddTile::execute(Game& board, std::vector<string>& user_input)
{
  try
  {
    // number of tiles beside the setted tile
    // for auto complete
    if (board.getNumberOfTiles() == 64)
    {
      throw NotEnoughTilesException();
    }

    Position p1;
    Tile t1(Tile::EMPTY_T, COLOR_RED);

    t1.setPlayer(board.getActivePlayer());
    // look up if the userinput is correct
    if (!(valideInput(user_input, t1, p1)))
    {
      return 1;
    }
    Tile empty_tile(Tile::EMPTY_T, EMPTY_C);

    t1.white_id_ = Tile::id_counter_++;
    t1.red_id_ = Tile::id_counter_++;

    Position center(0, 0);
    if ((board.getNumberOfTiles() == 0)
      && (t1.getColor() != COLOR_RED || p1 != center))
    {
      throw InvalidCoordinatesException();
    }
    if (board.getNumberOfTiles() && !adaptTile(board.field, t1, p1))
    {
      return 2;
    }

    for (auto& x : board.field)
    {
      if (*x.first == p1 && *x.second != empty_tile)
      {
        throw NotEmptyFieldException();
      }
    }

    bool replace = true;
    for (auto& y : board.field)
    {
      if (*y.first == p1 && *y.second == empty_tile)
      {
        delete y.second;
        board.field[y.first] = new Tile(t1);
        //y.second->white_id_ = Tile::id_counter_++;
        //y.second->red_id_ = Tile::id_counter_++;
        replace = false;
      }
    }

    // tile einfügen
    if (replace)
    {
      board.field.emplace(new Position(p1), new Tile(t1));
    }
    board.riseNumberOfTiles();

    // spielfeld vergrößern
    board.setMaximas(p1);

    // zwischenfelder mit leeren einträgen füllen
    if (board.getNumberOfTiles() > 2)
    {
      fillEmptyTiles(board);
    }

    // return 0 if nobody won 9 red 8 white
    return checkWin(board, t1);

    // if nobody won and tiles are not available
    if (board.getNumberOfTiles() == 64)
    {
      cout << "No more tiles left. Game ends in a draw!" << endl;
      return 4;
    }

    // falls alles geklappt hatt
    return 0;
  }
  catch (OutOfMemoryException& e1)
  {
    std::cout << e1.what() << std::endl;
  }
  catch (NotEnoughTilesException& e1)
  {
    std::cout << e1.what() << std::endl;
    return 3;
  }
  catch (InvalidCoordinatesException& e1)
  {
    std::cout << e1.what() << std::endl;
    return 2;
  }
  catch (NotEmptyFieldException& e1)
  {
    std::cout << e1.what() << std::endl;
    return 2;
  }
  
}

//------------------------------------------------------------------------------
bool AddTile::abfrage(bool abfrage1, bool &twisted, bool &lonely_tile, Tile &t1,
                      Color c1,Tile& t2)
  {
  try
  {
    //cout << t1.red_id_ << t2.red_id_ << t1.white_id_ << t2.white_id_ << endl;
    lonely_tile = false;
    if (abfrage1)
    {
      if (twisted)
      {
        throw ConnectedColorsMismatchException();
      }
      t1.setColor(t1.notTopColor());
      if (c1 == COLOR_WHITE)
      {
        t1.red_id_ = t2.red_id_;
      }
      if (c1 == COLOR_RED)
      {
        t1.white_id_ = t2.white_id_;
      }
      twisted = true;
    }
    else
    {
      if (c1 == COLOR_RED)
      {
        t1.red_id_ = t2.red_id_;
      }
      if (c1 == COLOR_WHITE)
      {
        t1.white_id_ = t2.white_id_;
      }
      twisted = true;
    }
    //cout << t1.red_id_ << t2.red_id_ << t1.white_id_ << t2.white_id_ << endl;
    return true;
  }
  catch (ConnectedColorsMismatchException& e1)
  {
    std::cout << e1.what() << std::endl;
    return false;
  }
}

//------------------------------------------------------------------------------
bool AddTile::adaptTile(std::map<Position*, Tile*> karte,
                        Tile &t1, Position p1)
{
  try
  {
    Tile empty_tile(Tile::EMPTY_T, EMPTY_C);
    // true wenn das tile angepasst wurde bzw schon richtig gelegen ist
    bool twisted = false;
    // falls angrenzend ein stein liegt
    bool lonely_tile = true;
    // positionen um den gelegten stein
    Position left(p1.getX() - 1, p1.getY());
    Position right(p1.getX() + 1, p1.getY());
    Position top(p1.getX(), p1.getY() - 1);
    Position buttom(p1.getX(), p1.getY() + 1);
    for (auto& x : karte)
    {
      if (*x.second == empty_tile)
      {
        continue;
      }
      if (*(x.first) == left &&
        !abfrage(x.second->getColorRight() != t1.getColorLeft(),
        twisted, lonely_tile, t1, t1.getColorLeft(), *x.second))
      {
        return false;
      }
      else if (*(x.first) == right &&
        !abfrage(x.second->getColorLeft() != t1.getColorRight(),
        twisted, lonely_tile, t1, t1.getColorRight(), *x.second))
      {
        return false;
      }
      else if (*(x.first) == top &&
        !abfrage(x.second->getColorButtom() != t1.getColorTop(),
        twisted, lonely_tile, t1, t1.getColorTop(), *x.second))
      {
        return false;
      }
      else if (*(x.first) == buttom &&
        !abfrage(x.second->getColorTop() != t1.getColorButtom(),
        twisted, lonely_tile, t1, t1.getColorButtom(), *x.second))
      {
        return false;
      }
      else
      {
        continue;
      }
    }
    if (lonely_tile)
    {
      throw NotConnectedFieldException();
    }
    return true;
  }
  catch (NotConnectedFieldException& e1)
  {
    std::cout << e1.what() << std::endl;
    return false;
  }
  
}

//------------------------------------------------------------------------------
bool AddTile::completeMap(std::map<Position*, Tile*> &karte,
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
void AddTile::fillEmptyTiles(Game& board)
{
  try
  {
    Tile empty_tile(Tile::EMPTY_T, EMPTY_C);
    bool wenn;
    for (signed int x = board.min_x_; x <= board.max_x_; x++)
    {
      for (signed int y = board.min_y_; y <= board.max_y_; y++)
      {
        wenn = true;
        Position empty_position(x, y);
        for (auto& x : board.field)
        {
          if (*x.first == empty_position)
          {
            wenn = false;
            break;
          }
        }
        if (wenn)
        {
          board.field.emplace(new Position(empty_position), new Tile(empty_tile));
        }
      }
    }
  }
  catch (OutOfMemoryException& e1)
  {
    std::cout << e1.what() << std::endl;
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
    if(max_x - min_x >= 8 || max_y - min_y >= 8)
    {
      cout << "Player " << color << " wins!" << endl;
      return 1;
    }
  }
  return 0;
}