#ifndef Commands_hpp
#define Commands_hpp
#include <iosfwd>
#include "Graph.hpp"
#include "WorkSpace.hpp"

namespace reznikova
{
  void helpCommand(std::ostream & out);
  void createCommand(std::istream & is, std::ostream & out, GraphList & list);
  void switchCommand(std::istream & is, std::ostream & out, GraphList & list);
  void addVertex(std::istream & is, std::ostream & out, GraphList & list);
  void addEdge(std::istream & is, std::ostream & out, GraphList & list);
  void addCommand(std::istream & is, std::ostream & out, GraphList & list);
  void deleteVertex(std::istream & is, std::ostream & out, GraphList & list);
  void deleteEdge(std::istream & is, std::ostream & out, GraphList & list);
  void deleteCommand(std::istream & is, std::ostream & out, GraphList & list);
  void capacityCommand(std::istream & is, std::ostream & out, GraphList & list);
  void adjacentCommand(std::istream & is, std::ostream & out, GraphList & list);
  void listCommand(std::ostream & out, GraphList & list);
  void graphNameCommand(std::ostream & out, GraphList & list);
  void bfsCommand(std::istream & is, std::ostream & out, GraphList & list);
  void readMatrix(std::istream & is, std::vector< std::vector< size_t > > & table);
}

#endif
