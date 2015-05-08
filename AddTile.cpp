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

#include "OutOfMemoryException.h"
#include "InvalidCoordinatesException.h"
#include "NotEmptyFieldException.h"
#include "NotConnectedFieldException.h"
#include "InvalidParameterException.h"
#include "ConnectedColorsMismatchException.h"
#include "NotEnoughTilesException.h"
#include "WrongParameterException.h"



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
  try
  {
    // input has to be 3 arguments
    if(user_input.size() != 3)
    {
      throw WrongParameterException();
    }
    // controll position input
    if(current_position.parse(user_input[1]))
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
    current_tile.setMove(board.moveID);
    // every tile gets a signature of the player
    current_tile.setPlayer(board.getActivePlayer());
    // look up if the user input is correct
    if(!(valideInput(user_input, current_tile, current_position)))
    {
      // abort addtile command
      return 1;
    }

    // fist tile has to be set in the point of orgin and topcolor red
    Position center(0, 0);
    if((board.getNumberOfTiles() == 0)
      && (current_tile.getColor() != COLOR_RED || current_position != center))
    {
      // abort addtile command
      throw InvalidCoordinatesException();
    }

    // if the position is already taken
    for (auto& it : board.field)
    {
      if(*it.first == current_position && *it.second != empty_tile)
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

        addTheTile(board, current_position, current_tile);

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
      return 1;
    }


    win(board,win_code);

    // if nobody won and tiles aren't anymore available -------------------------TODO difference invalide move and draw
    // if there is notile with the same moveid its not auto complete
    if (board.getNumberOfTiles() == 64)
    {
      // game over, tie
      std::cout << "No more tiles left. Game ends in a draw!" << std::endl;
      throw NotEnoughTilesException();
    }


    //TODO not do it if complete map
    board.togglePlayer();

    // if everything went well and game is not over
    if (board.getNumberOfTiles() >= 1)
    {
      graphicMode(board);
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
    return 0;
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
  return 0;
}

//------------------------------------------------------------------------------
void AddTile::graphicMode(Game& board)
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
void AddTile::addTheTile(Game& board, Position current_position, Tile current_tile)
{
  // for purposes of comparison
  Tile empty_tile(Tile::EMPTY_T,EMPTY_C);
  // replace empty tile with  new tile
  // only necessary if the position exists and filld with an empty tile
  bool replace = true;
  for (auto& it : board.field)
  {
    if(*it.first == current_position && *it.second == empty_tile)
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
      fillEmptyTiles(board, current_position);
    }
  }
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
    Position surrounding_position[4] = {Position(current_position.getX(),
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
        if(*(it.first) == surrounding_position[border] &&
           !colorCheck(it.second->getColor(it.second->oppositeBorder(border)) !=
                  current_tile.getColor(border),
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
int AddTile::completeMap(Game& board, Position &current_position, Tile &current_tile)
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

    // teoretical positions around the current tile
    Position surrounding_position[4] = {Position(it.first->getX(),
                                                 it.first->getY() - 1),
                                        Position(it.first->getX() + 1,
                                                 it.first->getY()),
                                        Position(it.first->getX(),
                                                 it.first->getY() + 1),
                                        Position(it.first->getX() - 1,
                                                 it.first->getY())};

    for(auto& nearby_tile: board.field)
    {
      if (*nearby_tile.second == empty_tile)
      {
        continue;
      }
      // search in surrounding positionen , TOP = 0 LEFT = 3
      for (int border = TOP; border <= LEFT; border++)
      {
        // is position in the surrounding
        if(*(nearby_tile.first) == surrounding_position[border])
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
          return 2;
          std::cout << "some error" << std::endl;
          // some error message
        }
        continue;
      }
      current_position = *it.first;

      current_tile.setType(expanded_tile.getTypeChar());
      current_tile.setColor(expanded_tile.getColor());
      return 0;
    }
  }
  return 1;
}

//------------------------------------------------------------------------------
void AddTile::fillEmptyTiles(Game& board, Position current_position)
{
  try
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
  catch (OutOfMemoryException& e1)
  {
    std::cout << e1.what() << std::endl;
  }
}

//------------------------------------------------------------------------------
int AddTile::winByLength(Game& board, Tile current_tile)
{
  Color colors[2] = {COLOR_WHITE, COLOR_RED};
  int who_won = 0;
  // control of the length of the red id and the white id of the current tile
  for (int i = 0; i < 2; i++)
  {
    signed int min_x = INT_MAX;
    signed int min_y = INT_MAX;
    signed int max_x = INT_MIN;
    signed int max_y = INT_MIN;
    // set minimas and maximas of each id
    for(auto& it: board.field)
    {
      if(it.second->getId(colors[i]) == current_tile.getId(colors[i]))
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
      if(colors[i] == COLOR_WHITE)
      {
        who_won += 1;
      }
      if(colors[i] == COLOR_RED)
      {
        who_won += 2;
      }
    }
  }
  switch(who_won)
  {
    case 1:
      return 1;
    case 2:
      return 2;
    case 3:
      // if both player would win in one move, the active player win
      if(board.getActivePlayer() == COLOR_WHITE)
      {
        // white player wins
        return 1;
      }
      else
      {
        // red player wins
        return 2;
      }
  }
  return 0;
}

//------------------------------------------------------------------------------
int AddTile::winByLoop(std::map<Position*, Tile*> field,
                     Tile &current_tile, Position current_position)
{
  // every tile gets a white and red identifications number
  current_tile.setId(COLOR_WHITE, id_counter_++);
  current_tile.setId(COLOR_RED, id_counter_++);

  // teoretical positions around the current tile
  Position surrounding_position[4] = {Position(current_position.getX(),
                                               current_position.getY() - 1),
                                      Position(current_position.getX() + 1,
                                               current_position.getY()),
                                      Position(current_position.getX(),
                                               current_position.getY() + 1),
                                      Position(current_position.getX() - 1,
                                               current_position.getY())};

  Color colors[2] = {COLOR_WHITE, COLOR_RED};
  // for each color a vector
  std::vector<int> id_to_merge[2] = {std::vector<int>(), std::vector<int>()};

  for(auto& it : field)
  {
    if(it.second->getType() == Tile::EMPTY_T &&
       it.second->getColor() == EMPTY_C)
    {
      continue;
    }
    // setting id by comparing ids of surrounding tiles , TOP = 0 LEFT = 3
    for (int border = TOP; border <= LEFT; border++)
    {
      if(*(it.first) == surrounding_position[border])
      {
        // for each color
        for(int i = 0; i < 2; i++)
        {
          if(current_tile.getColor(border) == colors[i])
          {
            current_tile.setId(colors[i], it.second->getId(colors[i]));
            // add ids of sorrounding tiles depending on the color
            id_to_merge[i].push_back(current_tile.getId(colors[i]));
          }
        }
      }
    }
  }
  // for each color
  for(int i = 0; i < 2; i++)
  {
    if(id_to_merge[i].size() >= 2)
    {
      // if 2 ids were connected by current tile
      for(auto& it: field)
      {
        if(it.second->getId(colors[i]) == id_to_merge[i][1])
        {
          it.second->setId(colors[i], id_to_merge[i][0]);
        }
      }
      if(current_tile.getId(colors[i]) == id_to_merge[i][1])
      {
        current_tile.setId(colors[i], id_to_merge[i][0]);
      }
      // if the same ids would be merged ->
      if(id_to_merge[i][1] == id_to_merge[i][0])
      {
        // loop detected
        return (i+1);
      }
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

//------------------------------------------------------------------------------
void AddTile::win(Game& board,std::vector<int> win_code)
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