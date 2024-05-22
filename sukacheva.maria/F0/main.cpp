#include <iostream>
#include <fstream>
#include <functional>
#include <map>
#include <iterator>
#include <limits>
#include "graph.hpp"
#include "commands.hpp"

int main()
{
  using namespace sukacheva;
  GraphList graphList;
  std::map< std::string, std::function < void(GraphList& graphList, std::istream& in, std::ostream& out) > > commands;
  {
    using namespace std::placeholders;
    commands["help"] = std::bind(help, _3);
    commands["create"] = std::bind(commandCreateGraph, _1, _2, _3);
    commands["add"] = std::bind(commandAdd, _1, _2, _3);
    commands["list"] = std::bind(printGraphList, _3, _1);
    commands["graphname"] = std::bind(graphName, _1, _3);
    commands["clear"] = std::bind(clearGraph, _1, _3);
    commands["capacity"] = std::bind(capacity, _1, _2, _3);
    commands["print"] = std::bind(commandPrint, _1, _2, _3);
    commands["delete"] = std::bind(commandDelete, _1, _2, _3);
    commands["work"] = std::bind(commandSwitch, _1, _2, _3);
    commands["weightTable"] = std::bind(printMatrix, _1, _3);
    commands["open"] = std::bind(commandOpen, _1, _2, _3);
    commands["save"] = std::bind(commandSave, _1, _2, _3);
  }
  std::string inputCommand = {};
  while (std::cin >> inputCommand)
  {
    try
    {
      commands.at(inputCommand)(graphList, std::cin, std::cout);
    }
    catch (const std::exception& e)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
