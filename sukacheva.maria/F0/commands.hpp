#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "graph.hpp"
#include "workspace.hpp"

namespace sukacheva
{
  void help(std::ostream& out);
  void createGraph(GraphList& graphList, std::string& graphName);
  void addVertex(GraphList& graphList, std::string& name);
  void addEdge(GraphList& graphList, std::string& start, std::string& end, size_t weight);
  void deleteVertex(GraphList& graphList, std::string& name);
  void deleteEdge(GraphList& graphList, std::string& start, std::string& end);
  void capacity(GraphList& graphList, std::istream& in, std::ostream& out);
  void graphName(GraphList& graphList, std::ostream& out);
  void deleteGraph(GraphList& graphList, std::string& graphName);
  void clearGraph(GraphList& graphList, std::ostream& out);
  void printGraphList(std::ostream& out, GraphList graphList);
  std::pair< std::map<size_t, size_t >, std::map< size_t, size_t > > getDistances(GraphList& graphList, std::string& name);
  std::vector< std::string > getPath(GraphList& graphList, std::string& start, std::string& end);
  void printPath(std::vector< std::string > path, std::ostream& out);
  std::map< size_t, std::vector< std::string > > getPathes(GraphList& graphList, std::string& name);
  void printPathes(GraphList& graphList, std::string& name, std::ostream& out);
  void printDistances(GraphList& graphList, std::string& name, std::ostream& out);

  void printMatrix(GraphList& graphList, std::ostream& out);
  void commandCreateGraph(GraphList& graphList, std::istream& in, std::ostream& out);
  void commandAdd(GraphList& graphList, std::istream& in, std::ostream& out);
  void commandPrint(GraphList& graphList, std::istream& in, std::ostream& out);
  void commandDelete(GraphList& graphList, std::istream& in, std::ostream& out);
  void commandSwitch(GraphList& graphList, std::istream& in, std::ostream& out);
  void commandOpen(GraphList& graphList, std::istream& in, std::ostream& out);
  void commandSave(GraphList& graphList, std::istream& in, std::ostream& out);
}

#endif
