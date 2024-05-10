#include <iostream>
#include <fstream>
#include <functional>
#include <limits>
#include "workspace.hpp"
#include "commands.hpp"
#include "inputFunctions.hpp"

int main(int argc, char* argv[])
{
  using namespace miheev;

  Graph initialGraph;
  Workspace workspace{{}, initialGraph};

  initWorkspace(argc, argv, workspace);

  std::map< std::string, std::function< std::ostream&(std::ostream&, std::istream&) > > commands;
  {
    using namespace std::placeholders;
    commands["node"] = std::bind(miheev::nodeCommand, _1, _2, workspace);
    commands["edge"] = std::bind(miheev::edgeCommand, _1, _2, workspace);
    commands["navigate"] = std::bind(miheev::navigateCommand, _1, _2, workspace);
    commands["list"] = std::bind(miheev::listCommand, _1, _2, workspace);
    commands["jump"] = std::bind(miheev::jumpCommand, _1, _2, workspace);
    commands["print"] = std::bind(miheev::printCommand, _1, _2, workspace);
  }

  std::string command = "";
  std::cout << "~> ";
  while(std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cout, std::cin);
    }
    catch (const std::invalid_argument& e)
    {
      std::cerr << e.what() << '\n';
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::out_of_range& e)
    {
      std::cerr << "invalid command\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::cout << "~> ";
  }

  return 0;
}