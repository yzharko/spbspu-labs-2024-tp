#include <iostream>
#include <map>
#include <limits>
#include "commands.hpp"
#include "accessoryFunctions.hpp"

int main()
{
  std::map< std::string, std::function< void & (std::string) > > commands;
  {
    commands["help"] = outputInfoAboutCommands;
    commands["input"] = ;
    commands["encode"] = ;
    commands["write"] = ;
    commands["set"] = ;
    commands["combine"] = ;
    commands["table"] = ;
    commands["decode"] = ;
    commands["delete"] = ;
    commands["clean"] = ;
    commands["save"] = ;
  }

  ponomarev::printWelcomeMessage(std::cout);

  std::string command = "";
  std::string type = "";
  while (std::cin >> command)
  {
    type = ponomarev::cutType(command);
    try
    {
      commands.at(type)(command);
    }
    catch (const std::logic_error &)
    {
      ponomarev::printInvalidCommandMessage(std::cout);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}
