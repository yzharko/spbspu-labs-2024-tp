#include <map>
#include <limits>
#include <functional>
#include <iostream>
#include "commands.hpp"
#include "accessoryFunctions.hpp"

int main()
{
  std::map< std::string, std::function< void (std::string &, ponomarev::HuffmanCode &) > > commands;
  {
    commands["help"] = ponomarev::outputInfoAboutCommands;
    commands["input"] = ponomarev::makeInput;
    commands["encode"] = ponomarev::chooseEncode;
    commands["write"] = ponomarev::writeTextIntoFile;
    commands["set"] = ponomarev::setDecode;
    commands["combine"] = ponomarev::combineFiles;
    commands["table"] = ponomarev::showTable;
    commands["decode"] = ponomarev::makeDecode;
    commands["delete"] = ponomarev::makeDelete;
    commands["clean"] = ponomarev::makeClean;
    commands["save"] = ponomarev::makeSave;
  }

  ponomarev::printWelcomeMessage(std::cout);
  std::string command = "";
  std::string type = "";
  ponomarev::HuffmanCode data;

  while (std::cin >> command)
  {
    type = ponomarev::cutType(command);
    try
    {
      commands.at(type)(command, data);
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
