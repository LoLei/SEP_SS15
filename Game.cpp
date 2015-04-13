//------------------------------------------------------------------------------
// Game.cpp
//
// Group: Group 9, study assistant Philip Loibl
//
// Authors: Markus Pichler 1331070
//
//------------------------------------------------------------------------------
//

#include "Game.h"

using std::cout;
using std::endl;
using std::string;

//------------------------------------------------------------------------------
Game::Game()
{
  activeplayer_ = COLOR_WHITE;
  starttile_ = NULL;
}

//------------------------------------------------------------------------------
void Game::setStartTile(Tile* starttile)
{
  starttile_ = starttile;
}

//------------------------------------------------------------------------------
void Game::setRunning(bool running)
{
  running_ = running;
}

//------------------------------------------------------------------------------
void Game::togglePlayer()
{
  switch (activeplayer_)
  {
    case COLOR_WHITE:
      activeplayer_ = COLOR_RED;
      break;
    case COLOR_RED:
      activeplayer_ = COLOR_WHITE;
      break;
  }
}

//------------------------------------------------------------------------------
Color Game::getActivePlayer()
{
  return activeplayer_;
}

//------------------------------------------------------------------------------
void Game::run()
{
  setRunning(true);

  std::map<Position*, Tile*> karte;

  Position p1;

  int count = 1;

  Tile starttile(Tile::TYPE_CROSS, COLOR_WHITE);
  Position center(0,0);

  string user_input;

  do
  {
    std::cout << "sep> ";
    std::getline(std::cin, user_input);
    // get first word in line -> command
    string str1;

    /*
    // If user enters blank line, prompt again
    if (str1 == "")
    {
    continue;
    }
    */

    str1 = user_input.substr(user_input.find_first_not_of(" "),
                             user_input.size());
    string str2 = str1.substr(0,str1.find_first_of(" "));
    // make lower case
    for(std::size_t it = 0; it != str2.size(); it++)
    {
      str2[it] = tolower(str2[it]);
    }
    // choose case of command
    if(str2 == "quit")
    {
      setRunning(false);
    }
    if(str2 == "write")
    {
      //TODO
      std::cout << "write" << std::endl;
    }
    if(str2 == "addtile")
    {
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
          Tile t1(t1.charToType(tile_type),COLOR_WHITE);

          bool ok = true;
          bool twist = false;
          bool found_tile = true;

          if(count == 1 && (t1 != starttile || p1 != center))
          {
            ok = false;
            cout << "not w+ or not (0,0)" << endl;
          }
          if(count != 1)
          {
            found_tile = false;
            Position *left = new Position(p1.getX() - 1,p1.getY());
            Position *right = new Position(p1.getX()+1,p1.getY());
            Position *top = new Position(p1.getX(),p1.getY()-1);
            Position *buttom = new Position(p1.getX(),p1.getY()+1);
            for (auto& x: karte)
            {
              if(*(x.first) == *left)
              {
                found_tile = true;
                if(x.second->getColorRight() != t1.getColorLeft() && ok)
                {
                  if(twist)
                    ok = false;
                  t1.setColor(t1.notTopColor());
                  twist = true;
                }
              }
              if(*(x.first) == *right)
              {
                found_tile = true;
                if(x.second->getColorLeft() != t1.getColorRight() && ok)
                {
                  if(twist)
                    ok = false;
                  t1.setColor(t1.notTopColor());
                  twist = true;
                }
              }
              if(*(x.first) == *top)
              {
                found_tile = true;
                if(x.second->getColorButtom() != t1.getColorTop() && ok)
                {
                  if(twist)
                    ok = false;
                  t1.setColor(t1.notTopColor());
                  twist = true;
                }
              }
              if(*(x.first) == *buttom)
              {
                found_tile = true;
                if(x.second->getColorTop() != t1.getColorButtom() && ok)
                {
                  if(twist)
                    ok = false;
                  t1.setColor(t1.notTopColor());
                  twist = true;
                }
              }
            }
            delete left;
            delete right;
            delete top;
            delete buttom;
          }
          if(ok && found_tile)
          {
            karte.emplace(new Position(p1.getX(),p1.getY()),new Tile(t1));
            count++;
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
  } while( running_ );
  //----------------------------------------------------------
  // alle einträge ausgeben
  for (auto& x: karte)
  {
    cout << x.first->toString() << ": " << x.second->getColorOut() <<" "
         << x.second->getTypeOut() << endl;
    delete x.first;
    delete x.second;
  }
}
