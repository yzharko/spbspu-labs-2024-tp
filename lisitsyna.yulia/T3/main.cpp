#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <limits>
#include <functional>
#include "ScopeGuard.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  if (argc == 1)
  {
    std::cerr << "Error 1: No filename to find.";
    return 1;
  }

  std::ifstream in(argv[1]);

  if (!in)
  {
    std::cerr << "Error 2: No such file.";
    in.close();
    return 2;
  }

  using lisitsyna::Polygon;
  /*using lisitsyna::Iofmtguard;*/
  Commands commands;

  while (!in.eof())
  {
    in.clear();
    std::copy(std::istream_iterator< Polygon >(in), std::istream_iterator< Polygon >(), std::back_inserter(commands.data));
  }

  in.close();

  std::map< std::string, std::function<void()> > commandMap;

  commandMap["AREA"] = std::bind(&Commands::getArea, std::ref(commands));
  commandMap["MAX"] = std::bind(&Commands::getMax, std::ref(commands));
  commandMap["MIN"] = std::bind(&Commands::getMin, std::ref(commands));
  commandMap["COUNT"] = std::bind(&Commands::getCount, std::ref(commands));
  commandMap["INFRAME"] = std::bind(&Commands::printInFrame, std::ref(commands));
  commandMap["RECTS"] = std::bind(&Commands::getRects, std::ref(commands));

  while (!std::cin.eof())
  {
    iofmtguard globalGuardian(std::cout);
    std::cin.clear();
    std::string command = "";
    std::cin >> command;
    auto temp = commandMap.find(command);
    if (!std::cin.eof())
    {
      if (temp != commandMap.cend())
      {
        temp->second();
      }
      else
      {
        commands.messageInvalidCommand(std::cout);
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
  }
  return 0;
}

