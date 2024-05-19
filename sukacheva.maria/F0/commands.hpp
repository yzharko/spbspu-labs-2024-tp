#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "graph.hpp"
#include "workspace.hpp"

namespace sukacheva
{
  void help(std::ostream& out);
  void createGraph(GraphList graphList, std::string graphName);
  void addVertex(GraphList graphList, std::string name);
  void addEdge(GraphList graphList, std::string start, std::string end, size_t weight);
  void deleteVertex(GraphList graphList, std::string name);
  void deleteEdge(GraphList graphList, std::string start, std::string end);
  void capacity(std::ostream& out, GraphList graphList);
  void graphName(std::ostream& out, GraphList graphList);
  void deleteGraph(GraphList graphList, std::string graphName);
  void clearGraph(GraphList graphList);
  void printGraphList(std::ostream& out, GraphList graphList);
}

#endif
