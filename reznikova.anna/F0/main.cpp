#include <iostream>
#include <map>
#include "Commands.hpp"

int main()
{
  using namespace reznikova;
  GraphList graphList;
  std::map< std::string, std::function < void(std::istream & is, std::ostream & out, GraphList & list) > > commands;
  {
    using namespace std::placeholders;
    commands["help"] = std::bind(helpCommand, _2);
    commands["create"] = std::bind(createCommand, _1, _2, _3);
    commands["add"] = std::bind(addCommand, _1, _2, _3);
    commands["switch"] = std::bind(switchCommand, _1, _2, _3);
    commands["delete"] = std::bind(deleteCommand, _1, _2, _3);
    commands["capacity"] = std::bind(capacityCommand, _1, _2, _3);
    commands["adjacent"] = std::bind(adjacentCommand, _1, _2, _3);
    commands["list"] = std::bind(listCommand, _2, _3);
    commands["graphName"] = std::bind(graphNameCommand, _2, _3);
    commands["BFS"] = std::bind(bfsCommand, _1, _2, _3);
  }
  std::string inputCommand;
  while (std::cin >> inputCommand)
  {
    try
    {
      commands.at(inputCommand)(std::cin, std::cout, graphList);
    }
    catch (const std::exception& e)
    {
      std::cout << e.what();
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
