//------------------------------------------------------------------------------
// Command.cpp
// From Palme website
// Group: Group 9, study assistant Philip Loibl
//
// Authors: 
// Tutors
// Created: 08.08.2011
// Last change: 29.05.2015
//------------------------------------------------------------------------------

#include "Command.h"


//------------------------------------------------------------------------------
Command::Command(std::string name) : command_name_(name)
{
}

//------------------------------------------------------------------------------
Command::~Command()
{
}

//------------------------------------------------------------------------------
const std::string &Command::getName() const
{
  return command_name_;
}
