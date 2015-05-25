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

#include <iostream>
#include <climits>
#include "Game.h"
#include "Tile.h"
#include "Position.h"
#include "AddTile.h"
#include "Write.h"


using std::string;

int AddTile::id_counter_ = 1;

//------------------------------------------------------------------------------
// Constructor
//
AddTile::AddTile() : Command("addtile")
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
  // input has to be 3 arguments
  if(user_input.size() != 3)
  {
    std::cout << "Error: Wrong parameter count!" << std::endl;
    return false;
  }
  // controll position input
  if(current_position.parse(user_input[1]))
  {
    try
    {
      // type input is only 1 sign
      if(user_input[2].size() != 1)
      {
        std::cout << "Invalid Parameters!" << std::endl;
        return false;
      }
      // if the sign is not valide, funktion return empty type(EMPTY_T)
      current_tile.setType(user_input[2][0]);
      if(current_tile.getType() == Tile::EMPTY_T)
      {
        std::cout << "Invalid Parameters!" << std::endl;
        return false;
      }
    }
    catch (...)
    {
      std::cout << "Invalid Parameters!" << std::endl;
      return false;
    }
  }
  else
  {
    std::cout << "Invalid Parameters!" << std::endl;
    return false;
  }
  return true;
}

//------------------------------------------------------------------------------
int AddTile::execute(Game &board, std::vector<string>& user_input)
{
  // tile and position which is going to be set
  Position current_position;
  Tile current_tile(Tile::EMPTY_T, COLOR_RED);
  current_tile.setMove(board.moveID);

  // look up if the user input is correct
  if(!(valideInput(user_input, current_tile, current_position)))
  {
    // abort addtile command
    return ABORT_ADDTILE;
  }
  // fist tile has to be set in the point of orgin and topcolor red
  Position center(0, 0);
  if((board.getNumberOfTiles() == 0)
    && (current_tile.getColor() != COLOR_RED || current_position != center))
  {
    // abort addtile command
    std::cout << "Invalid coordinates - first tile must be set on (0,0)" << std::endl;
    return INVALID_COORDINATES_ERROR;
  }

  // if the position is already taken
  for (auto& it : board.field)
  {
    if(*it.first == current_position && (it.second->getColor() != EMPTY_C &&
       it.second->getType() != Tile::EMPTY_T))
    {
      // abort addtile command
      std::cout << "Invalid coordinates - field not empty" << std::endl;
      return INVALID_COORDINATES_ERROR;
    }
  }

  // change topcolor, check if contact to other tile,
  // and check if all connected colors match
  if(board.getNumberOfTiles() > 0 &&
     adaptTile(board.field, current_tile, current_position))
  {
    // abort addtile command
    return ABORT_ADDTILE;
  }

  // code to identify who/if someone won by loop
  // 1 white, 2 red, 0 none
  // addtidionally add and merge ids
  std::vector<int> win_code;
  win_code.push_back(winByLoop(board.field, current_tile, current_position));
  if(win_code[win_code.size()-1] == 0)
  {
    win_code.pop_back();
  }

  // set new tile
  addTheTile(board, current_position, current_tile);

  // code to identify who/if someone won by length
  // 1 white, 2 red, 0 none
  if(board.getNumberOfTiles() >= 8)
  {
    win_code.push_back(winByLength(board, current_tile));
    if(win_code[win_code.size()-1] == 0)
    {
      win_code.pop_back();
    }
  }

  // autocomplete map, if there are obvious moves --------------------------------TODO
  int error = 0;

  while(error == 0 && board.getNumberOfTiles() > 2)
  {
    //current_tile.setMove(current_tile.getMove());

    error = completeMap(board, current_position, current_tile);
    if(!error)
    {
      win_code.push_back(winByLoop(board.field, current_tile, current_position));
      if(win_code[win_code.size()-1] == 0)
      {
        win_code.pop_back();
      }

      addTheTile(board, current_position, current_tile); //----------------------TODO memory error

      win_code.push_back(winByLength(board, current_tile));
      if(win_code[win_code.size()-1] == 0)
      {
        win_code.pop_back();
      }
    }
  }

  if(error == 2)
  {
    // if there is a none valide auto complete move
    for (auto& x: board.field)
    {
      if(x.second->getMove() == board.moveID)
      {
        delete x.first;
        delete x.second;
      }
    }
    return COMPLETE_ERROR;
  }


  win(board,win_code);

  // if nobody won and tiles aren't anymore available -------------------------TODO difference invalide move and draw
  // if there is notile with the same moveid its not auto complete
  if (board.getNumberOfTiles() == 64)
  {
    // game over, tie
    std::cout << "No more tiles left. Game ends in a draw!" << std::endl;
    std::cout << "Invalid move - not enough tiles left" << std::endl;
    board.setRunning(false);
    board.togglePlayer();
    return 0;
  }


  //TODO not do it if complete map
  board.togglePlayer();

  // if everything went well and game is not over
  if (board.getNumberOfTiles() >= 1)
  {
    graphicMode(board);
  }
  return 0;
}

//------------------------------------------------------------------------------
void AddTile::graphicMode(Game &board)
{
  // no tile set or a fail happend
  if(!board.getOutputFilename().empty())
  {
    Write new_file;
    std::vector<string> input;
    input.push_back("write");
    input.push_back(board.getOutputFilename());
    new_file.execute(board, input);
  }
}

//------------------------------------------------------------------------------
void AddTile::addTheTile(Game &board, Position current_position, Tile current_tile)
{
  // replace empty tile with  new tile
  // only necessary if the position exists and filld with an empty tile
  bool replace = true;
  for (auto& it : board.field)
  {
    if(*it.first == current_position && (it.second->getColor()
       == EMPTY_C && it.second->getType() == Tile::EMPTY_T))
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
    try
    {
      board.field.emplace(new Position(current_position), new Tile(current_tile));
    }
    catch(std::bad_alloc& ba)
    {
      std::cout << "Error: Out of Memory!" << std::endl; //----------TODO
      board.setRunning(false);
      return;
    }
    board.riseNumberOfTiles();

    // set size of field
    board.setMaximas(current_position);

    // insert empty tiles in field between maximas
    if (board.getNumberOfTiles() > 2)
    {
      fillEmptyTiles(board, current_position);
    }
  }
}

//------------------------------------------------------------------------------
bool AddTile::colorCheck(bool color_bool, bool &twisted, bool &lonely_tile,
                      Tile &current_tile)
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
      std::cout << "Invalid move - connected colors mismatch" << std::endl;
      return false;
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

//------------------------------------------------------------------------------
int AddTile::adaptTile(std::map<Position*, Tile*> field,
                        Tile &current_tile, Position current_position)
{
  // true if tile was twiste resp. topcolor war changed
  bool twisted = false;
  // true if there is no contact to another tile
  bool lonely_tile = true;

  for (auto& it : field)
  {
    // looking for nearby tiles
    if (it.second->getColor() == EMPTY_C && it.second->getType() == Tile::EMPTY_T)
    {
      continue;
    }
    // search in surrounding positionen
    for (Border border : {TOP, RIGHT, BOTTOM, LEFT})
    {
      // is position in the surrounding & do the colors match &
      // is contact to the field -
      if(*(it.first) == current_position.getNearbyPosition(border) &&
         !colorCheck(it.second->getColor(it.second->oppositeBorder(border)) !=
                current_tile.getColor(border),
                twisted, lonely_tile, current_tile))
      {
        // abort addtile command
        return ABORT_ADDTILE;
      }
    }
  }
  // if the new tile has no contact to the field
  if (lonely_tile)
  {
    // abort addtile command
    std::cout << "Invalid coordinates - field not connected to tile" << std::endl;
    return INVALID_COORDINATES_ERROR;
  }
  return 0;
}

//------------------------------------------------------------------------------
int AddTile::completeMap(Game &board, Position &current_position, Tile &current_tile)
{
  // for purposes of comparison
  Tile empty_tile(Tile::EMPTY_T,EMPTY_C);
  for(auto& it: board.field)
  {
    if(*it.second != empty_tile)
    {
      continue;
    }
    int found_tile = 0;
    // border colors of new tile
    Color surrounding_color[4] = {EMPTY_C, EMPTY_C, EMPTY_C, EMPTY_C};

    for(auto& nearby_tile: board.field)
    {
      if (*nearby_tile.second == empty_tile)
      {
        continue;
      }
      // search in surrounding positionen
      for (Border border : {TOP, RIGHT, BOTTOM, LEFT})
      {
        // is position in the surrounding
        if(*(nearby_tile.first) == it.first->getNearbyPosition(border))
        {
          // cound surrounding tiles
          found_tile++;
          // set surrounding colors
          surrounding_color[border] =
            nearby_tile.second->getColor(
              nearby_tile.second->oppositeBorder(border));
        }
      }
    }
    // if there are two sourrounding tiles with the same touching colors
    // of three tiles one tile will automatically set
    if(found_tile >= 2)
    {
      Tile expanded_tile(surrounding_color[0], surrounding_color[1],
                         surrounding_color[2], surrounding_color[3]);

      // if an empty tile was created the tile is not definite
      // or there is a disagreement
      if(expanded_tile == empty_tile)
      {
        if(found_tile > 2)
        {
          //-------------------------------------------------------------------------- TODO
          return SOME_ERROR;
          std::cout << "some error" << std::endl;
          // some error message
        }
        continue;
      }
      current_position = *it.first;

      current_tile.setType(expanded_tile.getTypeChar());
      current_tile.setColor(expanded_tile.getColor());
      return ADDTILE_SUCCESS;
    }
  }
  return 1;
}

//------------------------------------------------------------------------------
void AddTile::fillEmptyTiles(Game &board, Position current_position)
{
  Tile empty_tile(Tile::EMPTY_T,EMPTY_C);
  empty_tile.setMove(board.moveID);
  int current_x = current_position.getX();
  int current_y = current_position.getY();
  // if new tile was set on a edge
  if((current_x == board.max_x_ || current_x == board.min_x_) &&
     (current_y == board.max_y_ || current_y == board.min_y_))
  {
    // if the position is not in the tile bool is true and an empty tile
    // will be set
    bool set_empty_tile;
    for (signed int x = board.min_x_; x <= board.max_x_; x++)
    {
      for (signed int y = board.min_y_; y <= board.max_y_; y++)
      {
        set_empty_tile = true;
        Position empty_position(x, y);
        for (auto& it : board.field)
        {
          if (*it.first == empty_position)
          {
            set_empty_tile = false;
            break;
          }
        }
        if(set_empty_tile)
        {
          board.field.emplace(new Position(empty_position), new Tile(empty_tile));
        }
      }
    }
  }
  // if the new tile was set in the middle of the field
  else if(current_x == board.max_x_ || current_x == board.min_x_)
  {
    for(signed int y = board.min_y_; y <= board.max_y_; y++)
    {
      Position empty_position(current_x, y);
      if(empty_position == current_position)
      {
        continue;
      }
      else
      {
        board.field.emplace(new Position(empty_position), new Tile(empty_tile));
      }
    }
  }
  else if(current_y == board.max_y_ || current_y == board.min_y_)
  {
    for(signed int x = board.min_x_; x <= board.max_x_; x++)
    {
      Position empty_position(x, current_y);
      if(empty_position == current_position)
      {
        continue;
      }
      else
      {
        board.field.emplace(new Position(empty_position), new Tile(empty_tile));
      }
    }
  }
}

//------------------------------------------------------------------------------
int AddTile::winByLength(Game &board, Tile current_tile)
{
  int who_won = 0;
  // control of the length of the red id and the white id of the current tile
  for (Color colors : {COLOR_WHITE, COLOR_RED})
  {
    signed int min_x = INT_MAX;
    signed int min_y = INT_MAX;
    signed int max_x = INT_MIN;
    signed int max_y = INT_MIN;
    // set minimas and maximas of each id
    for(auto& it: board.field)
    {
      if(it.second->getId(colors) == current_tile.getId(colors))
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
    //check if the id goes over 8 rows or 8 lines
    if(max_x - min_x >= 7 || max_y - min_y >= 7)
    {
      if(colors == COLOR_WHITE)
      {
        who_won += 1;
      }
      if(colors == COLOR_RED)
      {
        who_won += 2;
      }
    }
  }
  // 1 white, 2 red, 0 none
  switch(who_won)
  {
    case WIN_WHITE:
      return WIN_WHITE;
    case WIN_RED:
      return WIN_RED;
    case 3:
      // if both player would win in one move, the active player win
      if(board.getActivePlayer() == COLOR_WHITE)
      {
        // white player wins
        return WIN_WHITE;
      }
      else
      {
        // red player wins
        return WIN_RED;
      }
  }
  return WIN_NONE;
}

//------------------------------------------------------------------------------
int AddTile::winByLoop(std::map<Position*, Tile*> field,
                     Tile &current_tile, Position current_position)
{
  // every tile gets a white and red identifications number
  current_tile.setId(COLOR_WHITE, id_counter_++);
  current_tile.setId(COLOR_RED, id_counter_++);

  // for each color a vector
  std::vector<int> id_to_merge[2] = {std::vector<int>(), std::vector<int>()};

  for(auto& it : field)
  {
    if(it.second->getType() == Tile::EMPTY_T &&
       it.second->getColor() == EMPTY_C)
    {
      continue;
    }
    // setting id by comparing ids of surrounding tiles
    for(Border border : {TOP, RIGHT, BOTTOM, LEFT})
    {
      if(*(it.first) == current_position.getNearbyPosition(border))
      {
        // for each color
        for(Color colors : {COLOR_WHITE, COLOR_RED})
        {
          if(current_tile.getColor(border) == colors)
          {
            current_tile.setId(colors, it.second->getId(colors));
            // add ids of sorrounding tiles depending on the color
            id_to_merge[colors - 1].push_back(current_tile.getId(colors));
          }
        }
      }
    }
  }
  // for each color
  for(Color colors : {COLOR_WHITE, COLOR_RED})
  {
    if(id_to_merge[colors - 1].size() >= 2)
    {
      // if 2 ids were connected by current tile
      for(auto& it: field)
      {
        if(it.second->getId(colors) == id_to_merge[colors - 1][1])
        {
          it.second->setId(colors, id_to_merge[colors - 1][0]);
        }
      }
      if(current_tile.getId(colors) == id_to_merge[colors - 1][1])
      {
        current_tile.setId(colors, id_to_merge[colors - 1][0]);
      }
      // if the same ids would be merged ->
      if(id_to_merge[colors - 1][1] == id_to_merge[colors - 1][0])
      {
        // loop detected
        return colors;
      }
    }
  }
  return WIN_NONE;
}

//------------------------------------------------------------------------------
void AddTile::whoWon(int win_code)
{
  if(win_code == 1)
  {
    std::cout << "Player white wins!" << std::endl;
    return;
  }
  if(win_code == 2)
  {
    std::cout << "Player red wins!" << std::endl;
    return;
  }
}

//------------------------------------------------------------------------------
void AddTile::win(Game &board,std::vector<int> win_code)
{
  // if both won in one move the active player wins
  if(win_code.size() > 1)
  {
    int same = 1;
    for(int i = 0; i < (int)win_code.size(); i++)
    {
      same *= win_code[i];
    }
    if(same == 1)
    {
      // game over, output white won
      board.setRunning(false);
      whoWon(win_code[0]);
      board.togglePlayer();
      return;
    }
    else
    {
      if(board.getActivePlayer() == COLOR_WHITE)
      {
        // white won
        // game over, output who won
        board.setRunning(false);
        whoWon(1);
        board.togglePlayer();
        return;
      }
      else
      {
        // red won
        // game over, output who won
        board.setRunning(false);
        whoWon(2);
        board.togglePlayer();
        return;
      }
    }
  }
  else if(win_code.size() == 1 && win_code[0] != 0)
  {
    // game over, output who won
    board.setRunning(false);
    whoWon(win_code[0]);
    board.togglePlayer();
    return;
  }
}
