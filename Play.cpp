//------------------------------------------------------------------------------
// AddTile.cpp
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors:
// Lorenz Leitner (1430211)
// Verena Niederwanger (1430778)
// Markus Pichler (1331070)
//------------------------------------------------------------------------------
//

#include "Play.h"
#include <cstdlib>

using std::string;


//------------------------------------------------------------------------------
// Constructor
//
Play::Play() : Command("Play")
{
}

//------------------------------------------------------------------------------
Play::~Play()
{
}

//------------------------------------------------------------------------------
int Play::execute(Game& board, std::vector<string>& user_input)
{
  // first tile
  if(board.getNumberOfTiles() == 0)
  {
    user_input.push_back("(0,0)");
    user_input.push_back(randomType());
    return 1;
  }

  // chack if i can win this round with length
  //checkLineLength(board,current_tile,board.getActivePlayer())
  lookForOpenEnds(board, user_input);

  if(int i = randomIDMove(board, user_input))
  {
    return i;
  }


  // if no winning move is possible
  if(int i = randomMove(board, user_input))
  {
    return i;
  }
  return 0;
}

//------------------------------------------------------------------------------
int Play::lookForOpenEnds(Game& board, std::vector<string>& user_input)
{
  /*
  std::vector<int> v;
  for (auto& x : board.field)
  {
    if(v.at(*x.second->getId(COLOR_RED))
  }
  */
  return 0;
}

//------------------------------------------------------------------------------
int Play::randomIDMove(Game& board, std::vector<string>& user_input)
{
  Position first(0,0);
  int myID;
  for(auto& var: board.field)
  {
    if(*var.first == first)
    {
      myID = var.second->getId(board.getActivePlayer());
    }
  }
  for(auto& var: board.field)
  {
    if(var.second->getId(board.getActivePlayer()) == myID)
    {
      int not_top = 0;
      int not_right = 0;
      int not_bottom = 0;
      int not_left = 0;
      Position current_position = *(var.first);
      if(var.second->getColor(LEFT) == board.getActivePlayer())
      {
        not_left = 1;
        Position left(current_position.getX() - 1,current_position.getY());
        for(auto& x : board.field)
        {
          if(*x.first == left)
          {
            not_left = 0;
            break;
          }
        }
      }
      if(var.second->getColor(RIGHT) == board.getActivePlayer())
      {
        not_right = 1;
        Position right(current_position.getX() + 1,current_position.getY());
        for(auto& x : board.field)
        {
          if(*x.first == right)
          {
            not_right = 0;
            break;
          }
        }
      }
      if(var.second->getColor(TOP) == board.getActivePlayer())
      {
        not_top = 1;
        Position top(current_position.getX(),current_position.getY() - 1);
        for(auto& x : board.field)
        {
          if(*x.first == top)
          {
            not_top = 0;
            break;
          }
        }
      }
      if(var.second->getColor(BOTTOM) == board.getActivePlayer())
      {
        not_bottom = 1;
        Position bottom(current_position.getX(),current_position.getY() + 1);
        for(auto& x : board.field)
        {
          if(*x.first == bottom)
          {
            not_bottom = 0;
            break;
          }
        }
      }
      if(not_top + not_bottom + not_left + not_right == 0)
      {
        continue;
      }
      else
      {
        if(not_top)
        {
          std::string pos = "(" + std::to_string(current_position.getX()) + ","
                          + std::to_string(current_position.getY() - 1) +")";
          user_input.push_back(pos);
          user_input.push_back(randomType("+"));
          return 1;
        }
        if(not_left)
        {
          std::string pos = "(" + std::to_string(current_position.getX() - 1) + ","
                          + std::to_string(current_position.getY()) +")";
          user_input.push_back(pos);
          user_input.push_back(randomType("+"));
          return 1;
        }
        if(not_right)
        {
          std::string pos = "(" + std::to_string(current_position.getX() + 1)
                          + "," + std::to_string(current_position.getY()) +")";
          user_input.push_back(pos);
          user_input.push_back(randomType("+"));
          return 1;
        }
        if(not_bottom)
        {
          std::string pos = "(" + std::to_string(current_position.getX())
                          + "," + std::to_string(current_position.getY() + 1) +")";
          user_input.push_back(pos);
          user_input.push_back(randomType("+"));
          return 1;
        }
      }
    }
  }
  return 0;
}

//------------------------------------------------------------------------------
int Play::randomMove(Game& board, std::vector<string>& user_input)
{
  Tile empty_tile(Tile::EMPTY_T,EMPTY_C);
  // if there are empty tiles
  for(auto& var: board.field)
  {
    if(*var.second == empty_tile)
    {
      int found_tile[2] = {0, 0};
      Color neighbor_color[4] = {EMPTY_C, EMPTY_C, EMPTY_C, EMPTY_C};

      Position current_position = *(var.first);
      Position left(current_position.getX() - 1,current_position.getY());
      Position right(current_position.getX()+1,current_position.getY());
      Position top(current_position.getX(),current_position.getY()-1);
      Position bottom(current_position.getX(),current_position.getY()+1);
      for(auto& nearby_tile: board.field)
      {
        if(*nearby_tile.second == empty_tile)
        {
          continue;
        }
        if(*(nearby_tile.first) == left)
        {
          found_tile[0]++;
          found_tile[1] = 3;
          neighbor_color[3] = nearby_tile.second->getColor(RIGHT);
        }
        else if(*(nearby_tile.first) == right)
        {
          found_tile[0]++;
          found_tile[1] = 1;
          neighbor_color[1] = nearby_tile.second->getColor(LEFT);
        }
        else if(*(nearby_tile.first) == top)
        {
          found_tile[0]++;
          found_tile[1] = 0;
          neighbor_color[0] = nearby_tile.second->getColor(BOTTOM);
        }
        else if(*(nearby_tile.first) == bottom)
        {
          found_tile[0]++;
          found_tile[1] = 2;
          neighbor_color[2] = nearby_tile.second->getColor(TOP);
        }
        else
        {
          continue;
        }
      }
      if(found_tile[0] == 1)
      {
        if(neighbor_color[found_tile[1]] != board.getActivePlayer())
        {
          continue;
        }
        user_input.push_back(current_position.toString());
        user_input.push_back(randomType());
        return 1;
      }
      if(found_tile[0] == 2)
      {
        user_input.push_back(current_position.toString());
        if(neighbor_color[3] == neighbor_color[0])
        {
          user_input.push_back(randomType("/"));
          return 1;
        }
        for(int i = 0; i < 4; i++)
        {
          if(neighbor_color[i] == neighbor_color[i+1])
          {
            if(i == 0 || i == 2)
            {
              user_input.push_back(randomType("\\"));
              return 1;
            }
            if(i == 1 || i == 3)
            {
              user_input.push_back(randomType("/"));
              return 1;
            }
          }
          if(neighbor_color[i] == neighbor_color[i+2])
          {
            user_input.push_back(randomType("+"));
            return 1;
          }
        }
        return 1;
      }
    }
  }

  // if there is no empty tile
  for(auto& var: board.field)
  {
    int not_top = 1;
    int not_right = 1;
    int not_bottom = 1;
    int not_left = 1;
    Position current_position = *(var.first);
    Position left(current_position.getX() - 1,current_position.getY());
    for(auto& x : board.field)
    {
      if(*x.first == left)
      {
        not_left = 0;
        break;
      }
    }
    Position right(current_position.getX() + 1,current_position.getY());
    for(auto& x : board.field)
    {
      if(*x.first == right)
      {
        not_right = 0;
        break;
      }
    }
    Position top(current_position.getX(),current_position.getY() - 1);
    for(auto& x : board.field)
    {
      if(*x.first == top)
      {
        not_top = 0;
        break;
      }
    }
    Position bottom(current_position.getX(),current_position.getY() + 1);
    for(auto& x : board.field)
    {
      if(*x.first == bottom)
      {
        not_bottom = 0;
        break;
      }
    }

    if(var.second->getColor(TOP) == board.getActivePlayer() && not_top)
    {
      user_input.push_back(top.toString());
      user_input.push_back(randomType());
      return 1;
    }
    else if(var.second->getColor(RIGHT) == board.getActivePlayer() && not_right)
    {
      user_input.push_back(right.toString());
      user_input.push_back(randomType());
      return 1;
    }
    else if(var.second->getColor(BOTTOM) == board.getActivePlayer() && not_bottom)
    {
      user_input.push_back(bottom.toString());
      user_input.push_back(randomType());
      return 1;
    }
    else if(var.second->getColor(LEFT) == board.getActivePlayer() && not_left)
    {
      user_input.push_back(left.toString());
      user_input.push_back(randomType());
      return 1;
    }
    else
    {
      continue;
    }
  }
  return 0;
}

//------------------------------------------------------------------------------
std::string Play::randomType()
{
  int random_int = rand() % 3;
  switch(random_int)
  {
    case 0:
      return "+";
    case 1:
      return "/";
    case 2:
      return "\\";
    default:
      break;
  }
  return "0";
}

//------------------------------------------------------------------------------
std::string Play::randomType(std::string not_type)
{
  int random_int = rand() % 3;
  switch(random_int)
  {
    case 0:
      if(not_type == "+")
      {
        return "/";
      }
      return "+";
    case 1:
      if(not_type == "/")
      {
        return "\\";
      }
      return "/";
    case 2:
      if(not_type == "\\")
      {
        return "+";
      }
      return "\\";
    default:
      break;
  }
  return "0";
}

/*
//------------------------------------------------------------------------------
int AddTile::checkLineLength(Game& board, Tile current_tile, Color color)
{
  // if a line goes over 8 lines or columns
  signed int min_x = INT_MAX;
  signed int min_y = INT_MAX;
  signed int max_x = INT_MIN;
  signed int max_y = INT_MIN;
  for(auto& var: board.field)
  {
    if(var.second->getId(color) == current_tile.getId(color))
    {
      if(var.first->getX() > max_x)
      {
        max_x = var.first->getX();
      }
      if(var.first->getY() > max_y)
      {
        max_y = var.first->getY();
      }
      if(var.first->getX() < min_x)
      {
        min_x = var.first->getX();
      }
      if(var.first->getY() < min_y)
      {
        min_y = var.first->getY();
      }
    }
  }
  if(max_x - min_x >= 7 || max_y - min_y >= 7)
  {
    return 1;
  }
  return 0;
}
*/
