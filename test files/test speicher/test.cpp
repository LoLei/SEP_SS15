#include <map>
#include <iostream>
#include "Position.h"
#include "Tile.h"
#include <iomanip>

using std::cout;
using std::endl;
using std::string;
void check(string a)
{
  cout << std::setfill ('-') << std::setw (30) << a << endl;
}


int main()
{
  std::map<Position*, Tile*> karte;
  Tile t1;
  //Tile *t2 = new Tile(Tile::TYPE_CROSS,COLOR_WHITE);
  Position p1;
  int count = 1;
  Color activeplayer_ = COLOR_WHITE;
  Tile starttile;
  Position center(0,0);

  string user_input;
  do
  {
    std::cout << "sep> ";
    std::getline(std::cin, user_input);
    // get first word in line -> command
    string str1;
    str1 = user_input;
    // If user enters bank line, prompt again
    if (str1 == "")
    {
      continue;
    }
    str1 = user_input.substr(user_input.find_first_not_of(" "),
                             user_input.size());
    string str2 = str1.substr(0,str1.find_first_of(" "));
    // make lower case
    for(std::size_t it = 0; it != str2.size(); it++)
    {
      str2[it] = tolower(str2[it]);
    }
    if(str2 == "addtile")
    {
      string str3 = user_input.substr(user_input.find_first_of("("),
                                      user_input.find_last_of(")") -
                                      user_input.find_first_of("(") + 1);
      if(p1.parse(str3))
      {
        t1.setType(user_input.at(user_input.find_last_of("+\\/")));
        t1.setColor(activeplayer_);
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
          //cout << "left: " << left->toString() << endl;
          Position *right = new Position(p1.getX()+1,p1.getY());
          Position *top = new Position(p1.getX(),p1.getY()-1);
          Position *buttom = new Position(p1.getX(),p1.getY()+1);
          for (auto& x: karte)
          {
            if(*(x.first) == *left)
            {
              check("found left");
              found_tile = true;
              if(x.second->getColorRight() != t1.getColorLeft() && ok)
              {
                if(twist)
                  ok = false;
                t1.setColor(t1.notTopColor());
                twist = true;
                check("drehen");
              }
            }
            if(*(x.first) == *right)
            {
              check("found right");
              found_tile = true;
              if(x.second->getColorLeft() != t1.getColorRight() && ok)
              {
                if(twist)
                  ok = false;
                t1.setColor(t1.notTopColor());
                twist = true;
                check("drehen");
              }
            }
            if(*(x.first) == *top)
            {
              check("found top");
              found_tile = true;
              if(x.second->getColorButtom() != t1.getColorTop() && ok)
              {
                if(twist)
                  ok = false;
                t1.setColor(t1.notTopColor());
                twist = true;
                check("drehen");
              }
            }
            if(*(x.first) == *buttom)
            {
              check("found buttom");
              found_tile = true;
              if(x.second->getColorTop() != t1.getColorButtom() && ok)
              {
                if(twist)
                  ok = false;
                t1.setColor(t1.notTopColor());
                twist = true;
                check("drehen");
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
          check("added tile");
          count++;
        }
      }
    }
  } while(user_input != "quit");


  for (auto& x: karte)
  {
    cout << x.first->toString() << ": " << x.second->getColorOut() <<" "
         << x.second->getTypeOut() << endl;
    delete x.first;
    delete x.second;
  }
  return 0;
}
