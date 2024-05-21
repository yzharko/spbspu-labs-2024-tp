#ifndef Commands_hpp
#define Commands_hpp
#include <iosfwd>
#include "Graph.hpp"
#include "WorkSpace.hpp"

namespace reznikova
{
  void helpCommand(std::ostream & out);
  void addVertex(std::istream & is, std::ostream & out, GraphList & list);
  void addEdge(std::istream & is, std::ostream & out, GraphList & list);
  void addCommand(std::istream & is, std::ostream & out, GraphList & list);
}

#endif
