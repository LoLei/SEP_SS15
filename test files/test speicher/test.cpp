#include <map>
#include <iostream>
#include "Position.h"
#include "Tile.h"

using std::cout;
using std::endl;
using std::string;
void check(int a)
{
  cout << "--------" << a <<"--------" << endl;
}


int main()
{
  std::map<Position*, Tile*> karte;
  Tile t1(Tile::TYPE_CROSS,COLOR_RED);
  //Tile *t2 = new Tile(Tile::TYPE_CROSS,COLOR_WHITE);
  Position p1;

  Color activeplayer_ = COLOR_WHITE;
  
  string user_input;
  do
  {
    std::cout << "sep> ";
    std::getline(std::cin, user_input);
    // get first word in line -> command
    string str1 = user_input.substr(user_input.find_first_not_of(" "), user_input.size());
    string str2 = str1.substr(0,str1.find_first_of(" "));
    // make lower case
    for(std::size_t it = 0; it != str2.size(); it++)
    {
      str2[it] = tolower(str2[it]);
    }
    if(str2 == "addtile")
    {
      string str3 = user_input.substr(user_input.find_first_of("("),user_input.find_last_of(")") - user_input.find_first_of("(") + 1);
      if (p1.parse(str3))
      {
        t1.setType(user_input.at(user_input.find_last_of("+\\/")));
        t1.setColor(activeplayer_);
        //karte[p1] = t1;
        karte.emplace(new Position(p1.getX(),p1.getY()),new Tile(t1));
      }
    
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
  } while(user_input != "quit");





/*
  string x = "(0,1)";
  if(p1.parse(x))
  {
    karte[p1] = t1;
  }
*/
  //Position *p2 = new Position;
  //for (int i = 0; i< 9 ; i++)
  {
    //p2->setX(i);
    //p2->setY(i);
    //karte.emplace(new Position(i,i),t2);
  }

  

  for (auto& x: karte)
  {
    std::cout << x.first->toString() << ": " << x.second->getColorOut() <<" " << x.second->getTypeOut() << endl;
    delete x.first;
    delete x.second;
  }
  //delete t1;
  return 0;
}