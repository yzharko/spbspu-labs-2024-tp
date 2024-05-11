#include <iostream>
#include <fstream>
#include <functional>
#include <limits>
#include "workspace.hpp"
#include "commands.hpp"
#include "IOFunctions.hpp"

#include <sstream>

void foo(miheev::Workspace& w)
{
  std::stringstream ss("test\n1-2:1 1-3:1 2-3:1");
  miheev::Graph test;
  ss >> test;
  w.current = test;
}

int main(int argc, char* argv[])
{
  using namespace miheev;

  Graph initialGraph;
  initialGraph.name = "untitled";
  Workspace workspace{{}, initialGraph};
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
  }

  std::string command = "";
  std::cout << "[" << workspace.current.name <<"]~> ";
  while(std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cout, std::cin, workspace);
    }
    catch (const std::invalid_argument& e)
    {
      std::cerr << e.what() << '\n';
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::out_of_range& e)
    {
      std::cerr << "invalid command\n";
      std::cerr << e.what() << '\n';
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::runtime_error& e)
    {
      std::cerr << e.what() << '\n';
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::cout << "[" << workspace.current.name <<"]~> ";
  }

  return 0;
}