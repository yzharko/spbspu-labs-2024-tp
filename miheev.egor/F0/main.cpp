#include <iostream>
#include <fstream>
#include <functional>
#include <limits>
#include "workspace.hpp"
#include "commands.hpp"
#include "IOFunctions.hpp"

#include <sstream>

int main(int argc, char* argv[])
{
  using namespace miheev;

  Graph initialGraph;
  initialGraph.name = "untitled";
  Workspace workspace{{}, initialGraph, true};
  initWorkspace(argc, argv, workspace);

  std::map< std::string, std::function< std::ostream&(std::ostream&, std::istream&, Workspace&) > > commands;
  {
    using namespace std::placeholders;
    commands["node"] = miheev::commands::node;
    commands["edge"] = miheev::commands::edge;
    commands["graph"] = miheev::commands::graph;
    commands["navigate"] = miheev::commands::navigate;
    commands["list"] = miheev::commands::list;
    commands["jump"] = miheev::commands::jump;
    commands["print"] = miheev::commands::print;
    commands["save"] = miheev::commands::save;
    commands["help"] = miheev::commands::help;
    commands["quit"] = miheev::commands::quit;
  }

  std::string command = "";
  while(workspace.isActive && !std::cin.eof())
  {
    std::cout << "[" << workspace.current.name <<"]~> ";
    std::cin >> std::ws >> command;

    if (command == "" && std::cin.eof())
    {
      commands.at("quit")(std::cout, std::cin, workspace) << '\n';
      continue;
    }
    try
    {
      commands.at(command)(std::cout, std::cin, workspace);
    }
    catch (const std::invalid_argument& e)
    {
      sendMessage(std::cerr, e.what());
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::out_of_range& e)
    {
      sendMessage(std::cerr, "[ERROR] invalid command");
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::runtime_error& e)
    {
      sendMessage(std::cerr, e.what());
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  miheev::sendMessage(std::cout, "[EXIT] Goodbye!");
  return 0;
}
