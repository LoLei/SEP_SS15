//------------------------------------------------------------------------------
// position.cpp
//
// Group: 9, study assistant: Philipp Loibl
//
// Authors: Verena Niederwanger (1430778)
//------------------------------------------------------------------------------
//
#include "Position.h"
#include <string>
#include <sstream>
#include <iostream>

//default constructor
Position::Position()
{
}

//constructor
Position::Position(signed int x, signed int y)
{
}

//copy constructor
Position::Position(const Position &copy)
{
}

//destructor
Position::~Position()
{
}

//parse ACHTUNG: ÜBERPRÜFUNG 
bool Position::parse(std::string input)
{
	bool ok;
	std::string string_1 = "";
	std::string string_2 = "";
	bool char_found = false;
	int i;
	input = "";
	std::cin >> input;
	input = input.substr(1, input.length - 1);
	for (i = 0; i < input.length; i++)
	{
		if (char_found == false)
		{
			if (input[i] == ',')
			{
				char_found = true;
			}
			else
			{
				string_1 += input[i];
			}
		}
		else
		{
			string_2 += input[i];
		}
	}
	//check it!
	char check[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	int x;
	int y;
	int z; 

	for (x = 0; x < check[10]; x++)
	{
		for (y = 0; y < string_1.length; y++)
		{
			if (string_1[0] == '-')
			{
				continue;
			}
			else if (string_1[y] == '-')
			{
				break;
				 ok = false;
			}
		}
		for (z = 0; z < string_2.length ; z++)
		{
			if (string_2[0] = '-')
			{
				continue;
			}
			else if (string_2[z] == '-')
			{
				break;
				ok = false;
			}
	
		}
	}
	x = std::stoi(string_1);
	y = std::stoi(string_2);

}

//toString
std::string Position::toString()
{
	std::string output = "(";
	output += std::to_string(x) + "," + std::to_string(y) +")";
	return output;
}

