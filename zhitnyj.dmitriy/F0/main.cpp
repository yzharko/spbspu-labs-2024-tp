#include <iostream>
#include <map>
#include "Graph.hpp"
#include "Commands.hpp"

int main() {
  Graph graph;
  std::map< std::string, std::function< void(std::istream &, std::ostream &, Graph &) > > cmds;

  cmds["help"] = std::bind(helpCommand, std::placeholders::_2);
  cmds["add"] = std::bind(addCommand, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  cmds["del"] = std::bind(delCommand, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  cmds["dijkstra"] = std::bind(dijkstraCommand, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  cmds["path"] = std::bind(shortestPathCommand, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  cmds["show"] = std::bind(showGraphCommand, std::placeholders::_2, std::placeholders::_3);
  cmds["save"] = std::bind(saveGraphCommand, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  cmds["load"] = std::bind(loadGraphCommand, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  cmds["update"] = std::bind(updateEdgeCommand, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  cmds["neighbors"] = std::bind(neighborsCommand, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  cmds["connected"] = std::bind(isConnectedCommand, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

  try {
    std::string cmd;
    while (std::cin >> cmd) {
      auto it = cmds.find(cmd);
      if (it != cmds.end()) {
        it->second(std::cin, std::cout, graph);
      }
      else {
        printInvalidCommand(std::cout);
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
  }
  catch (const std::logic_error &e) {
    std::cerr << "There was an error: " << e.what();
  }

  return 0;
}
