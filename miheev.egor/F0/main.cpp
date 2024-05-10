#include <iostream>
#include <fstream>
#include <functional>
#include <limits>
#include "workspace.hpp"
#include "commands.hpp"
#include "inputFunctions.hpp"

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
  // std::map< std::string, Graph > initialGraphs;
  Workspace workspace{{}, initialGraph};

  // workspace.current.printAllEdges(std::cout);
  initWorkspace(argc, argv, workspace);
  // workspace.current.printAllEdges(std::cout);
  // foo(workspace);
  // workspace.current.printAllEdges(std::cout);

  std::map< std::string, std::function< std::ostream&(std::ostream&, std::istream&, Workspace&) > > commands;
  {
    using namespace std::placeholders;
    commands["node"] = miheev::commands::node;
    commands["edge"] = miheev::commands::edge;
    commands["navigate"] = miheev::commands::navigate;
    commands["list"] = miheev::commands::list;
    commands["jump"] = miheev::commands::jump;
    commands["print"] = miheev::commands::print;
  }

  std::string command = "";
  std::cout << "~> ";
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
    std::cout << "~> ";
  }

  return 0;
}