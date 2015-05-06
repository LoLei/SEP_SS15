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

#include "AddTile.h"

using std::string;

int AddTile::id_counter_ = 0;

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
bool AddTile::valideInput(std::vector<string> user_input, Tile &current_tile,
  Position &current_position)
{
  try
  {
    // input has to be 3 arguments
    if (user_input.size() != 3)
    {
      throw WrongParameterException();
    }
    // controll position input
    if (current_position.parse(user_input[1]))
    {
      try
      {
        // type input is only 1 sign
        if(user_input[2].size() != 1)
        {
          throw InvalidParameterException();
        }
        // if the sign is not valide, funktion return empty type(EMPTY_T)
        current_tile.setType(user_input[2][0]);
        if(current_tile.getType() == Tile::EMPTY_T)
        {
          throw InvalidParameterException();
        }
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
    // for purposes of comparison
    Tile empty_tile(Tile::EMPTY_T,EMPTY_C);
    // tile and position which is going to be set
    Position current_position;
    Tile current_tile(Tile::EMPTY_T, COLOR_RED);
    // every tile gets a signature of the player
    current_tile.setPlayer(board.getActivePlayer());
    // look up if the userinput is correct
    if (!(valideInput(user_input, current_tile, current_position)))
    {
      // abort addtile command
      return 1;
    }
    // every tile gets a white and red identifications number
    current_tile.setWhiteId(id_counter_++);
    current_tile.setRedId(id_counter_++);

    // fist tile has to be set in the point of orgin and topcolor red
    Position center(0, 0);
    if ((board.getNumberOfTiles() == 0)
      && (current_tile.getColor() != COLOR_RED || current_position != center))
    {
      // abort addtile command
      throw InvalidCoordinatesException();
    }

    // if the position is already taken
    for (auto& it : board.field)
    {
      if (*it.first == current_position && *it.second != empty_tile)
      {
        // abort addtile command
        throw NotEmptyFieldException();
      }
    }

    // change topcolor, check if contact to other tile,
    // and check if all connected colors match
    if(board.getNumberOfTiles() > 0 &&
       adaptTile(board.field, current_tile, current_position))
    {
      // abort addtile command
      return 1;
    }

    // code to identify who/if someone won by loop
    // 1 white, 2 red, 0 none
    int win_code_by_loop = 0;
    win_code_by_loop = winByLoop(board.field, current_tile, current_position);

    // set new tile
    // replace empty tile with  new tile
    // only necessary if the position exists and filld with an empty tile
    bool replace = true;
    for (auto& it : board.field)
    {
      if (*it.first == current_position && *it.second == empty_tile)
      {
        // for clean replacement
        delete it.second;
        board.field[it.first] = new Tile(current_tile);
        board.riseNumberOfTiles();
        replace = false;
      }
    }

    // set new tile
    if (replace)
    {
      board.field.emplace(new Position(current_position), new Tile(current_tile));
      board.riseNumberOfTiles();

      // set size of field
      board.setMaximas(current_position);

      // insert empty tiles in field between maximas
      if (board.getNumberOfTiles() > 2)
      {
        fillEmptyTiles(board);
      }
    }

    // code to identify who/if someone won by length
    // 1 white, 2 red, 0 none
    int win_code_by_length = 0;
    win_code_by_length = winByLength(board, current_tile);

    int win_code = 0;
    // if both won in one move the active player wins
    if(win_code_by_length && win_code_by_loop &&
       (win_code_by_length != win_code_by_loop))
    {
      if(board.getActivePlayer() == COLOR_WHITE)
      {
        // white won
        win_code = 1;
      }
      else
      {
        // red won
        win_code = 2;
      }
    }
    else
    {
      if(win_code_by_length)
      {
        win_code = win_code_by_length;
      }
      else
      {
        win_code = win_code_by_loop;
      }
    }

    // game over, output who won
    if(win_code)
    {
      board.setRunning(false);
      whoWon(win_code);
      board.togglePlayer();
      return 2;
    }

    // if nobody won and tiles aren't anymore available
    if (board.getNumberOfTiles() == 64)
    {
      // game over, tie
      throw NotEnoughTilesException();
    }

  }
  catch (OutOfMemoryException& e1)
  {
    std::cout << e1.what() << std::endl;
  }
  catch (NotEnoughTilesException& e1)
  {
    std::cout << e1.what() << std::endl;
    board.setRunning(false);
    board.togglePlayer();
    return 2;
  }
  catch (InvalidCoordinatesException& e1)
  {
    std::cout << e1.what() << std::endl;
    return 1;
  }
  catch (NotEmptyFieldException& e1)
  {
    std::cout << e1.what() << std::endl;
    return 1;
  }

  // autocomplete map, if there are obvious moves
  if(completeMap(board.field, user_input))
  {
    execute(board, user_input);
  }
  // if everything went well and game is not over, active player switch
  board.togglePlayer();
  return 0;
}

//------------------------------------------------------------------------------
bool AddTile::colorCheck(bool color_bool, bool &twisted, bool &lonely_tile,
                      Tile &current_tile)
{
  try
  {
    // true if there is no contact to another tile
    lonely_tile = false;
    // check if the touching color of the nearby tile match with the current
    if (color_bool)
    {
      // if one color already match and one dosen't
      if (twisted)
      {
        // abort addtile command
        throw ConnectedColorsMismatchException();
      }
      // twist the tile in order that the colors match resp. chage topcolor
      current_tile.setColor(current_tile.notTopColor());
      // now one color match
      twisted = true;
    }
    else
    {
      // the touching color of the nearby tile match with the current
      twisted = true;
    }
    return true;
  }
  catch (ConnectedColorsMismatchException& e1)
  {
    std::cout << e1.what() << std::endl;
    return false;
  }
}



int AddTile::oppositeBorder(int border)
{
  switch(border)
  {
    case TOP:
      return BOTTOM;
    case RIGHT:
      return LEFT;
    case BOTTOM:
      return TOP;
    case LEFT:
      return RIGHT;
  }
  return 5;
}
//------------------------------------------------------------------------------
int AddTile::adaptTile(std::map<Position*, Tile*> field,
                        Tile &current_tile, Position current_position)
{
  try
  {
    // for purposes of comparison
    Tile empty_tile(Tile::EMPTY_T,EMPTY_C);
    // true if tile was twiste resp. topcolor war changed
    bool twisted = false;
    // true if there is no contact to another tile
    bool lonely_tile = true;
    // teoretical positions around the current tile
    Position position[4] = {Position(current_position.getX(),
                                     current_position.getY() - 1),
                            Position(current_position.getX() + 1,
                                     current_position.getY()),
                            Position(current_position.getX(),
                                     current_position.getY() + 1),
                            Position(current_position.getX() - 1,
                                     current_position.getY())};

    for (auto& it : field)
    {
      // looking for nearby tiles
      if (*it.second == empty_tile)
      {
        continue;
      }
      // search in surrounding positionen , TOP = 0 LEFT = 3
      for (int border = TOP; border <= LEFT; border++)
      {
        // is position in the surrounding & do the colors match &
        // is contact to the field -
        if(*(it.first) == position[border] &&
           !colorCheck(it.second->getColor(oppositeBorder(border)) != current_tile.getColor(border),
                  twisted, lonely_tile, current_tile))
        {
          // abort addtile command
          return 1;
        }
      }
    }
    // if the new tile has no contact to the field
    if (lonely_tile)
    {
      // abort addtile command
      throw NotConnectedFieldException();
    }
    return 0;
  }
  catch (NotConnectedFieldException& e1)
  {
    std::cout << e1.what() << std::endl;
    return 1;
  }
  return 0;
}

//------------------------------------------------------------------------------
bool AddTile::completeMap(std::map<Position*, Tile*> &field,
  std::vector<string> &forAddtile)
{
  Tile empty_tile(Tile::EMPTY_T,EMPTY_C);
  for(auto& it: field)
  {
    if(*it.second != empty_tile)
    {
      continue;
    }
    int found_tile = 0;
    Color left_color = EMPTY_C;
    Color right_color = EMPTY_C;
    Color top_color = EMPTY_C;
    Color bottom_color = EMPTY_C;

    Position current_position = *(it.first);
    Position left(current_position.getX() - 1,current_position.getY());
    Position right(current_position.getX()+1,current_position.getY());
    Position top(current_position.getX(),current_position.getY()-1);
    Position bottom(current_position.getX(),current_position.getY()+1);
    for(auto& nearby_tile: field)
    {
      if(*nearby_tile.second == empty_tile)
      {
        continue;
      }
      if(*(nearby_tile.first) == left)
      {
        found_tile++;
        left_color = nearby_tile.second->getColor(RIGHT);
      }
      else if(*(nearby_tile.first) == right)
      {
        found_tile++;
        right_color = nearby_tile.second->getColor(LEFT);
      }
      else if(*(nearby_tile.first) == top)
      {
        found_tile++;
        top_color = nearby_tile.second->getColor(BOTTOM);
      }
      else if(*(nearby_tile.first) == bottom)
      {
        found_tile++;
        bottom_color = nearby_tile.second->getColor(TOP);
      }
      else
      {
        continue;
      }
    }
    if(found_tile >= 2)
    {
      Tile expanded_tile(left_color, right_color, top_color, bottom_color);
      if(expanded_tile == empty_tile)
      {
        continue;
      }
      forAddtile[1] = it.first->toString();
      forAddtile[2] = expanded_tile.getTypeOut();
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
    Tile empty_tile(Tile::EMPTY_T,EMPTY_C);
    bool wenn;
    for (signed int x = board.min_x_; x <= board.max_x_; x++)
    {
      for (signed int y = board.min_y_; y <= board.max_y_; y++)
      {
        wenn = true;
        Position empty_position(x, y);
        for (auto& it : board.field)
        {
          if (*it.first == empty_position)
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
int AddTile::winByLength(Game& board, Tile current_tile)
{
  if(checkLineLength(board,current_tile,COLOR_WHITE))
  {
    return 1;
  }
  if(checkLineLength(board,current_tile,COLOR_RED))
  {
    return 2;
  }
  return 0;
}

//------------------------------------------------------------------------------
int AddTile::checkLineLength(Game& board, Tile current_tile, Color id_color)
{
  // if a line goes over 8 lines or columns
  signed int min_x = INT_MAX;
  signed int min_y = INT_MAX;
  signed int max_x = INT_MIN;
  signed int max_y = INT_MIN;
  for(auto& it: board.field)
  {
    if(it.second->getId(id_color) == current_tile.getId(id_color))
    {
      if(it.first->getX() > max_x)
      {
        max_x = it.first->getX();
      }
      if(it.first->getY() > max_y)
      {
        max_y = it.first->getY();
      }
      if(it.first->getX() < min_x)
      {
        min_x = it.first->getX();
      }
      if(it.first->getY() < min_y)
      {
        min_y = it.first->getY();
      }
    }
  }
  if(max_x - min_x >= 7 || max_y - min_y >= 7)
  {
    return 1;
  }
  return 0;
}

//------------------------------------------------------------------------------
void AddTile::idCheck(Tile &current_tile, Color color_to_match,Tile& tile_beside,
                      std::vector<int> &red_id_to_merge,
                      std::vector<int> &white_id_to_merge)
{
  if(color_to_match == COLOR_RED)
  {
    current_tile.setRedId(tile_beside.getId(COLOR_RED));
    red_id_to_merge.push_back(current_tile.getId(COLOR_RED));
  }
  if(color_to_match == COLOR_WHITE)
  {
    current_tile.setWhiteId(tile_beside.getId(COLOR_WHITE));
    white_id_to_merge.push_back(current_tile.getId(COLOR_WHITE));
  }
}

//------------------------------------------------------------------------------
int AddTile::winByLoop(std::map<Position*, Tile*> field,
                     Tile &current_tile, Position current_position)
{
  Tile empty_tile(Tile::EMPTY_T,EMPTY_C);

  Position left(current_position.getX() - 1, current_position.getY());
  Position right(current_position.getX() + 1, current_position.getY());
  Position top(current_position.getX(), current_position.getY() - 1);
  Position bottom(current_position.getX(), current_position.getY() + 1);

  std::vector<int> red_id_to_merge;
  std::vector<int> white_id_to_merge;

  for(auto& it : field)
  {
    if(*it.second == empty_tile)
    {
      continue;
    }
    if(*(it.first) == left)
    {
      idCheck(current_tile, current_tile.getColor(LEFT),*it.second,
              red_id_to_merge, white_id_to_merge);
    }
    else if(*(it.first) == right)
    {
      idCheck(current_tile,current_tile.getColor(RIGHT),*it.second,
              red_id_to_merge, white_id_to_merge);
    }
    else if(*(it.first) == top)
    {
      idCheck(current_tile,current_tile.getColor(TOP),*it.second,
              red_id_to_merge, white_id_to_merge);
    }
    else if(*(it.first) == bottom)
    {
      idCheck(current_tile,current_tile.getColor(BOTTOM),*it.second,
              red_id_to_merge, white_id_to_merge);
    }
    else
    {
      continue;
    }
  }

  if(red_id_to_merge.size() >= 2)
  {
    for(auto& it: field)
    {
      if(it.second->getId(COLOR_RED) == red_id_to_merge[1])
      {
        it.second->setRedId(red_id_to_merge[0]);
      }
    }
    if(current_tile.getId(COLOR_RED) == red_id_to_merge[1])
    {
      current_tile.setRedId(red_id_to_merge[0]);
    }
    if(red_id_to_merge[1] == red_id_to_merge[0])
    {
      return 2;
      //win
    }
  }
  if(white_id_to_merge.size() >= 2)
  {
    for(auto& it: field)
    {
      if(it.second->getId(COLOR_WHITE) == white_id_to_merge[1])
      {
        it.second->setWhiteId(white_id_to_merge[0]);
      }
    }
    if(current_tile.getId(COLOR_WHITE) == white_id_to_merge[1])
    {
      current_tile.setWhiteId(white_id_to_merge[0]);
    }
    if(white_id_to_merge[0] == white_id_to_merge[1])
    {
      return 1;
      //win
    }
  }
  return 0;
}

//------------------------------------------------------------------------------
int AddTile::whoWon(int win_code)
{
  if(win_code == 1)
  {
    std::cout << "Player white wins!" << std::endl;
    return 5;
  }
  if(win_code == 2)
  {
    std::cout << "Player red wins!" << std::endl;
    return 5;
  }
  return 0;
}

